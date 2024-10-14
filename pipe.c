

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


//==================================================================================
//構造体


typedef enum e_token_kind
{
	TOKEN_UNKNOWN,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_EOF,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
	TOKEN_LPARENT,
	TOKEN_RPARENT,
}	t_token_kind;

typedef struct s_token
{
	char			*token;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

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
//token_not_pipe_count()

t_token *token_not_pipe_count(t_token *token)
{
	while (token && token->kind != TOKEN_PIPE)
	{
		token = token->next;
	}
	if (token && token->kind == TOKEN_PIPE)
	{
		token = token->next;
	}
	return(token);
	
}

//==============================================================================
//dicision_args

char **decision_args(t_token *token)
{
	t_token *tmp_token;
	int i;

	tmp_token = token;
	int list_elem_num = 0;

	while (tmp_token && tmp_token->kind != TOKEN_PIPE)
	{
		list_elem_num++;
		// printf("token: %s\n",tmp_token->token);
		tmp_token = tmp_token->next;
	}

	char	**args = (char**)malloc(sizeof(char*) * (list_elem_num + 1));

	tmp_token = token;
	i = 0;
	while(tmp_token && tmp_token->kind != TOKEN_PIPE)
	{
		args[i] = strdup(tmp_token->token);
		tmp_token = tmp_token->next;
		i++;
	}
	args[i] = NULL;
	
	int num = 0;
	while(args[num])
	{
		printf("args[%d] : %s\n", num, args[num]);
		num++;
	}

	return(args);
}


//==================================================================================
//==================================================================================
//com_token_pipe


void	com_token_pipe(t_token *token, int num_com)
{
	int	fds[2];
	int	keep_fd = 0;
	int	i;
	pid_t	pid;
	t_token	*tmp_token;
	char **args;

	tmp_token = token;
	i = 0;
	while (i < num_com && tmp_token)
	{
		if (tmp_token->kind == TOKEN_WORD)
		{
			if (i < num_com - 1 && pipe(fds) == -1)
			{
				exit;
			}
			pid = fork();
			if (pid == -1)
			{
				exit(1);
			}
			if (pid == 0)
			{
				fd_input_child(keep_fd);
				if (i < num_com - 1)
				{
					fd_output_child(fds);
				}
				// printf("befor -> tmp->token %s\n", tmp_token->token);

				args = decision_args(tmp_token);
				// printf("args[0] = %s\n args[1] = %s\n", args[0], args[1]);
				execve(find_command(args[0]), args, NULL);

				free(args);
				exit(0);
			}
			else if (pid > 0)
				keep_fd_update(fds, &keep_fd, i, num_com);
			i++;
		}
		// printf("after -----> tmp->token %s\n", tmp_token->token);

		tmp_token = token_not_pipe_count(tmp_token);
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


int main()
{
    t_token *token1 = create_token("ls", TOKEN_WORD);
    t_token *token2 = create_token("-l", TOKEN_WORD);

    t_token *token3 = create_token("|", TOKEN_PIPE);
    
	t_token *token4 = create_token("grep", TOKEN_WORD);
    t_token *token5 = create_token(".c", TOKEN_WORD);
    
	t_token *token6 = create_token("|", TOKEN_PIPE);
    
	t_token *token7 = create_token("wc", TOKEN_WORD);
	t_token *token8 = create_token("-l", TOKEN_WORD);

    // トークンをリンク
    token1->next = token2;
    token2->next = token3;
    token3->next = token4;
    token4->next = token5;
    token5->next = token6;
    token6->next = token7;
	token7->next = token8;

    // パイプを用いてコマンド実行
    com_token_pipe(token1, 1);

    return (0);
}
