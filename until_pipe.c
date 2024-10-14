/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   until_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryomori <ryomori@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-11 04:00:18 by ryomori           #+#    #+#             */
/*   Updated: 2024-10-11 04:00:18 by ryomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   until_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryomori <ryomori@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-10 03:26:01 by ryomori           #+#    #+#             */
/*   Updated: 2024-10-10 03:26:01 by ryomori          ###   ########.fr       */
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


//================================================================================================
//until

//(ex)>ls | grep .c | wc -l のcommandの部分をcountする。この場合だと３。
// int	com_count_pipe(t_node *node)
// {
// 	t_node *com_count_node;
// 	int	count;

// 	com_count_node = node;
// 	count = 0;

// 	while(com_count_node)
// 	{
// 		if (com_count_node->kind == NODE_CMD)
// 			count++;
// 		com_count_node = com_count_node->next;
// 	}
// 	return (count);
// }



//================================================================================================
//decision_args

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
	// TODO: free args elements
	// while (/* condition */)
	// {
	// 	/* code */
	// }
	// // TODO: free args

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

//===============================================================================================
//main関数 + create_token + create_node

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

	    // t_tokenのリストを作成
    t_token *token1 = create_token("ls", TOKEN_WORD);
    t_token *token2 = create_token("-l", TOKEN_WORD);
    t_token *token3 = create_token("-a", TOKEN_WORD);
	t_token *token4 = create_token("/home", TOKEN_WORD);

    // token1 -> token2 -> token3 をリンク
    token1->next = token2;
    token2->next = token3;
	token3->next = token4;

    // t_nodeのリストを作成
    t_node *node1 = create_node(token1, TOKEN_WORD);


	 char **result = decision_args(node1);

    // 取得した結果を解放
	printf("node1 args:\n");
    for (int i = 0; result[i] != NULL; i++) {
        printf("token [%d]: %s\n", i, result[i]);
    }

	return (0);
}


// int main()
// {
// 	// parse_element element[] = {{"/bin/ls",{"/bin/ls", "NULL"}, NULL}, {"/bin/grep", {"/bin/grep", ".c", "NULL"}, NULL}, {"/usr/bin/wc", {"/usr/bin/wc", "-l", "NULL"}, NULL}};

// 	// int i = 3; //commandの数

// 	    //node1   t_tokenのリストを作成
//     t_token *token1 = create_token("ls", TOKEN_WORD);
//     // t_token *token2 = create_token("-l", TOKEN_WORD);
//     // t_token *token3 = create_token("-a", TOKEN_WORD);
// 	// t_token *token4 = create_token("/home", TOKEN_WORD);

// 		//node2
// 	t_token *token5 = create_token("|", TOKEN_OPE);

// 		//node3
// 	t_token	*token6 = create_token("grep", TOKEN_WORD);
// 	t_token	*token7 = create_token(".c", TOKEN_WORD);

// 		//node4
// 	t_token	*token8 = create_token("|", TOKEN_OPE);

// 		//node5
// 	t_token *token9 = create_token("wc", TOKEN_WORD);
// 	t_token *token10 = create_token("-l", TOKEN_WORD);

//     // node1のリンクーーー＞token1 -> token2 -> token3 をリンク
//     // token1->next = token2;
//     // token2->next = token3;
// 	// token3->next = token4;

// 	// node2のリンク(パイプ)
	
// 	// node3のリンク
// 	token6->next = token7;

// 	// node4のリンク(パイプ)
	
// 	// noke5のリンク
// 	token9->next = token10;



//     // t_nodeのリストを作成
//     t_node *node1 = create_node(token1, NODE_CMD);
// 	t_node *node2 = create_node(token5, NODE_OPE);
// 	t_node *node3 = create_node(token6, NODE_CMD);
// 	t_node *node4 = create_node(token8, NODE_OPE);
// 	t_node *node5 = create_node(token9, NODE_CMD);


// 	node1->next = node2;
// 	node2->next = node3;
// 	node3->next = node4;
// 	node4->next = node5;

// 	printf("command数 : %d\n", com_count_pipe(node1));
// 	// command_pipe(node1, 3);
// 	return (0);
// }
