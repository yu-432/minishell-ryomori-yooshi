/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryomori <ryomori@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-11 03:59:08 by ryomori           #+#    #+#             */
/*   Updated: 2024-10-11 03:59:08 by ryomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// typedef struct
// {
// 	char	*path;
// 	char	*args[3];
// 	char	**envp;
// } parse_element;
//--------------------------------------------------------------------
//構造体

typedef struct s_token	t_token;
typedef struct s_node	t_node;
typedef enum {
	TOKEN_WORD,//文字列
	TOKEN_OPE,//operator
	TOKEN_META,//メタ文字
	TOKEN_EOF, //終端
}	t_token_kind;

typedef enum {
	NODE_EOF,
	NODE_CMD,
	NODE_OPE
}	t_node_kind;

struct	s_token	{
	char 			*token;
	t_token_kind	kind;
	t_token			*next;
}	;

struct s_node {
	t_token			*args;
	t_node_kind		kind;
	t_node			*next;
}	;
//-----------------------------------------------------------------
//split

static char	*ft_strndup(const char *s1, int len)
{
	char	*s_cpy;

	s_cpy = (char *)malloc((len + 1) * sizeof(char));
	if (s_cpy == NULL)
		return (NULL);
	if (len > 0)
		memcpy(s_cpy, s1, len);
	s_cpy[len] = '\0';
	return (s_cpy);
}

static int	count_words(const char *s, char c)
{
	int	flag;
	int	count;

	flag = 1;
	count = 0;
	while (*s)
	{
		if (*s == c)
			flag = 1;
		else if (flag == 1)
		{
			count++;
			flag = 0;
		}
		s++;
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	**all_free(char **result, int index)
{
	while (index--)
		free(result[index]);
	free(result);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		index;
	int		i;

	if (!s)
		return (NULL);
	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	index = 0;
	i = 0;
	while (index < count_words(s, c))
	{
		if (s[i] == c)
			i++;
		else
		{
			result[index++] = ft_strndup(&s[i], word_len(s + i, c));
			if (result[index - 1] == NULL)
				return (all_free(result, index));
			i += word_len(s + i, c);
		}
	}
	result[index] = NULL;
	return (result);
}
//-------------------------------------------------------------------------
//strjoin

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	char			*value;

	if (!s1 || !s2)
		return (NULL);
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	value = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (value == NULL)
		return (NULL);
	memcpy(value, s1, s1_len);
	memcpy(value + s1_len, s2, s2_len + 1);
	return (value);
}
//---------------------------------------------------------------------------
//find_command

char	*find_command(char *line)
{
	int		i;
	char	**path;
	char	*slash;
	char	*joined;

	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		slash = ft_strjoin("/", line);
		joined = ft_strjoin(path[i], slash);
		free(slash);
		if (!access(joined, F_OK))
			return (free(path), joined);
		free(joined);
		i++;
	}
	free(path);
	return (NULL);
}
//==============================================================================
//dicision_args

char **decision_args(t_node *node)
{
	t_node	*tmp_node;
	t_token *tmp_token;

	tmp_node = node;
	tmp_token = tmp_node->args;
	int list_elem_num = 0;
				
	while (tmp_token != NULL)
	{
		list_elem_num++;
		tmp_token = tmp_token->next;
	}
	printf("list_elem_num: %d\n", list_elem_num);

	char **args = (char**)malloc(sizeof(char*) * (list_elem_num + 1));

	tmp_token = tmp_node->args;
	int x = 0;
	while(tmp_token != NULL)
	{
		args[x] = strdup(tmp_token->token);
		tmp_token = tmp_token->next;
		x++;
	}
	x++;
	args[x] = NULL;

	// args の中身
	int a = 0;
	while(args[a])
	{
		printf("args[%d]: %s\n", a, args[a]);
		a++;
	}

	return(&*args);


}

//===============================================================================================
//fd_input

void	fd_input_child(int keep_fd)
{
	if (keep_fd != 0)
	{
		if (dup2(keep_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(keep_fd);
	}
}

//===============================================================================================
//fd_output

void	fd_output_child(int *fds)
{
	close(fds[0]);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fds[1]);
}

//===============================================================================================
//keep_fd_update

void	keep_fd_update(int *fds, int *keep_fd, int i, int num_com)
{
	if (*keep_fd != 0)
		close(*keep_fd);
	if (i < num_com - 1)
	{
		close(fds[1]);
		*keep_fd = fds[0];
	}
}

//==============================================================================
//pipe

void	command_pipe(t_node *node, int num_com)
{
	int	fds[2];
	int	keep_fd = 0;
	pid_t	pid;
	int	i = 0;
	t_node *tmp = node;
	char **args;

	while (i < num_com && tmp)
	{
		if (tmp->kind == NODE_CMD)
		{
			if (i < num_com - 1 && pipe(fds) == -1)
				exit(1);
			pid = fork();
			if (pid == -1)
				exit(1);
			if (pid == 0)
			{
				fd_input_child(keep_fd);
				if (i < num_com - 1)
					fd_output_child(fds);
				args = decision_args(tmp);
				execve(find_command(args[0]), args, NULL);
				free(args);
				exit(0);
			}
			else if (pid > 0)
				keep_fd_update(fds, &keep_fd, i, num_com);
			i++;
		}
		tmp = tmp->next;
		while (tmp && tmp->kind == NODE_OPE)
			tmp = tmp->next;
	}
	i = 0;
	while (i < num_com)
	{
		wait(NULL);
		i++;
	}
}


t_token *create_token(char *str, t_token_kind kind) {
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token) {
        perror("Failed to allocate memory for token");
        exit(1);
    }
    new_token->token = strdup(str);  // 文字列をコピー
    new_token->kind = kind;
    new_token->next = NULL;
    return new_token;
}

// t_node の新しい要素を作成
t_node *create_node(t_token *args, t_node_kind kind) {
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node) {
        perror("Failed to allocate memory for node");
        exit(1);
    }
    new_node->args = args;
    new_node->kind = kind;
    new_node->next = NULL;
    return new_node;
}


int main()
{
	// parse_element element[] = {{"/bin/ls",{"/bin/ls", "NULL"}, NULL}, {"/bin/grep", {"/bin/grep", ".c", "NULL"}, NULL}, {"/usr/bin/wc", {"/usr/bin/wc", "-l", "NULL"}, NULL}};

	// int i = 3; //commandの数

	    //node1   t_tokenのリストを作成
    t_token *token1 = create_token("echo", TOKEN_WORD);
    // t_token *token2 = create_token("-l", TOKEN_WORD);
    // t_token *token3 = create_token("-a", TOKEN_WORD);
	// t_token *token4 = create_token("/home", TOKEN_WORD);

		//node2
	t_token *token5 = create_token("|", TOKEN_OPE);

		//node3
	t_token	*token6 = create_token("wc", TOKEN_WORD);
	t_token	*token7 = create_token("-l", TOKEN_WORD);

		//node4
	// t_token	*token8 = create_token("|", TOKEN_OPE);

		//node5
	// t_token *token9 = create_token("wc", TOKEN_WORD);
	// t_token *token10 = create_token("-l", TOKEN_WORD);

    // node1のリンクーーー＞token1 -> token2 -> token3 をリンク
    // token1->next = token2;
    // token2->next = token3;
	// token3->next = token4;

	// node2のリンク(パイプ)
	
	// node3のリンク
	token6->next = token7;

	// node4のリンク(パイプ)
	
	// noke5のリンク
	// token9->next = token10;



    // t_nodeのリストを作成
    t_node *node1 = create_node(token1, NODE_CMD);
	t_node *node2 = create_node(token5, NODE_OPE);
	t_node *node3 = create_node(token6, NODE_CMD);
	// t_node *node4 = create_node(token8, NODE_OPE);
	// t_node *node5 = create_node(token9, NODE_CMD);


	node1->next = node2;
	node2->next = node3;
	// node3->next = node4;
	// node4->next = node5;


	command_pipe(node1, 2);


	return (0);
}


// #include <sys/wait.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// typedef struct
// {
// 	char	*path;
// 	char	*args[3];
// 	char	**envp;
// } parse_element;



// void	command_pipe(parse_element element[], int num_com)
// {
// 	int	fds[2];
// 	int	keep_fd = 0;
// 	pid_t	pid;
// 	int	i = 0;


// 	while (i < num_com)
// 	{
// 		if (i < num_com - 1 && pipe(fds) == -1)
// 		{
// 			exit(1);
// 		}

// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			exit(1);
// 		}

// 		if (pid == 0)
// 		{
// 			if (keep_fd != 0)
// 			{
// 				if (dup2(keep_fd, STDIN_FILENO) == -1)
// 				{
// 					exit(1);
// 				}
// 				close(keep_fd);
// 			}

// 			if (i < num_com - 1)
// 			{
// 				close(fds[0]);
// 				if (dup2(fds[1], STDOUT_FILENO) == -1)
// 				{
// 					exit(1);
// 				}
// 				close(fds[1]);
// 			}

// 			execve(element[i].path, element[i].args, element[i].envp);
// 			exit(0);
// 		}
// 		else if (pid > 0)
// 		{
// 			if (keep_fd != 0)
// 				close(keep_fd);
			
// 			if (i < num_com - 1)
// 			{
// 				close (fds[1]);
// 				keep_fd = fds[0];
// 			}
// 		}
// 		i++;
// 	}

// 	i = 0;
// 	while (i < num_com)
// 	{
// 		wait(NULL);
// 		i++;
// 	}
// }

// int main()
// {
// 	parse_element element[] = {{"/bin/ls",{"/bin/ls", NULL}, NULL}, {"/bin/grep", {"/bin/grep", ".c", NULL}, NULL}, {"/usr/bin/wc", {"/usr/bin/wc", "-l", NULL}, NULL}};

// 	int i = 3; //commandの数

// 	command_pipe(element, i);
// 	return (0);
// }
