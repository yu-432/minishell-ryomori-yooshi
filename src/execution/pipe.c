#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/lexer.h"
#include "../../header/init.h"
#include "../../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// TODO: 後で消す
extern char **environ;
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

//---------------------------------------------------------------------------
//find_command

char	*find_command(char *line)
{
	int		i;
	char	**path;
	char	*slash;
	char	*joined;

	if(!access(line, F_OK))
		return(ft_strndup(line,strlen(line)));
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
		if (tmp_token->kind == TOKEN_REDIRECT_IN ||
			tmp_token->kind == TOKEN_REDIRECT_OUT ||
			tmp_token->kind == TOKEN_REDIRECT_APPEND ||
			tmp_token->kind == TOKEN_REDIRECT_HEREDOC)
		{
			tmp_token = tmp_token->next;
			if (tmp_token)
				tmp_token = tmp_token->next;
		}
		else
		{
			list_elem_num++;
			tmp_token = tmp_token->next;
		}
	}

	fprintf(stderr, "num = %d\n", list_elem_num);

	char	**args = (char**)malloc(sizeof(char*) * (list_elem_num + 1));
	if (!args)
	{
		perror("malloc");
		exit(1);
	}
	
	tmp_token = token;
	i = 0;
	while(tmp_token && tmp_token->kind != TOKEN_PIPE)
	{
		if (tmp_token->kind == TOKEN_REDIRECT_IN ||
			tmp_token->kind == TOKEN_REDIRECT_OUT ||
			tmp_token->kind == TOKEN_REDIRECT_APPEND ||
			tmp_token->kind == TOKEN_REDIRECT_HEREDOC)
		{
			tmp_token = tmp_token->next;
			if (tmp_token)
				tmp_token = tmp_token->next;
		}
		else
		{
			args[i++] = strdup(tmp_token->token);
			tmp_token = tmp_token->next;
		}
	}
	args[i] = NULL;
	// int num = 0;
	// while(args[num])
	// {
	// 	printf("args[%d] : %s\n", num, args[num]);
	// 	num++;
	// }

	return(args);
}

//==================================================================================
//==================================================================================
//herdoc_process
int	herdoc_process(char *docDelimiter, int stdout_fd_copy)
{
	char	*line = NULL;
	int		fd[2];

	if (dup2(stdout_fd_copy, STDOUT_FILENO) == -1)
	{
		close(stdout_fd_copy);
		perror("dup2");
		return (-1);
	}
	if (pipe(fd) < 0)
	{
		perror("pipe");
	}
	// fd = open("/tmp/heredoc_tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while ((line = readline("heredoc> ")) != NULL)
	{
		if (strncmp(line, docDelimiter, strlen(docDelimiter)) == 0 && line[strlen(docDelimiter)] == '\0')
		{
			free(line);
			break;
		}
		write(fd[1], line, strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}

	close(fd[1]);
	return (fd[0]);

}

//==================================================================================
//==================================================================================
//redirect

int	redirections(t_token *token, int stdout_copy)
{
	int	fd;

	fd = -1;
	while (token && token->kind != TOKEN_PIPE)
	{
	fprintf(stderr, "token->token-----------------%s\n", (token)->token);

		if ((token)->kind == TOKEN_REDIRECT_IN)
		{
			fprintf(stderr, "TOKEN_REDIRECT_IN %s\n", (token)->token);
			token = (token)->next;
			if (!token)
			{
				fprintf(stderr, "Error: Token redirect < IN\n");
				return (-1);
			}
			fd = open((token)->token, O_RDONLY);
			if (fd == -1)
			{
				perror("open");
				return (-1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				perror("dup2");
				return (-1);
			}
			close (fd);
		}
		else if ((token)->kind == TOKEN_REDIRECT_OUT)
		{
			fprintf(stderr, "TOKEN_REDIRECT_OUT %s\n", (token)->token);
			token = (token)->next;
			if (!token)
			{
				fprintf(stderr, "Error: Token resirect > OUT\n");
				return (-1);
			}	
			fd = open((token)->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			fprintf(stderr, "fd = %d\n", fd);
			if (fd == -1)
			{
				perror("open");
				return (-1);
			}
			if(dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				perror("dup2");
				return (-1);
			}
			close(fd);
		}
		else if ((token)->kind == TOKEN_REDIRECT_APPEND)
		{
			token = (token)->next;
			if (!token)
			{
				fprintf(stderr, "Error: Token redirect >> append\n");
				return (-1);
			}
			fd = open((token)->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("open");
				return(-1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				perror("dup2");
				return (-1);
			}
			close(fd);
		}
		else if ((token)->kind == TOKEN_REDIRECT_HEREDOC)
		{
			fprintf(stderr, "[debug]: TOKEN------%s\n", (token)->token);
			token = (token)->next;
			if (!token)
			{
				fprintf(stderr, "Error: Token resirect << HEREDOC\n");
				return (-1);
			}
			fd = herdoc_process((token)->token, stdout_copy);
			if (fd == -1)
			{
				fprintf(stderr, "Error processing heredoc\n");
				return (-1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				perror("dup2");
				return (-1);
			}
			close(fd);
		}
		// else
		// {
		// 	continue;
		// }
		token = (token)->next;
	}
	return (0);
}


/*
** com_token_pipe
** args: t_token *token, int num_com
*/
void	com_token_pipe(t_token *token, int num_com)
{
	int	fds[2];
	int	keep_fd = 0;
	int	i;
	pid_t	pid;
	t_token	*tmp_token;
	char **args;
	int	stdout_copy = dup(STDOUT_FILENO);

	tmp_token = token;
	i = 0;
	while (i < num_com && tmp_token)
	{
		if (tmp_token->kind == TOKEN_WORD)
		{
			fprintf(stderr, "i = %d\n", i);
			if (i < num_com - 1 && pipe(fds) == -1)
			{
				perror("pipe");
				exit(1);
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(1);
			}
			if (pid == 0)
			{
				fd_input_child(keep_fd);
				if (i < num_com - 1)
				{
					fd_output_child(fds);
				}
				fprintf(stderr, "tmp->token123 %s\n", tmp_token->token);
				if (redirections(tmp_token, stdout_copy) == -1)
				{
					exit(1);
				}
				fprintf(stderr, "tmp->token543 %s\n", tmp_token->token);
				

				args = decision_args(tmp_token);
				fprintf(stderr, "find_command :%s\n", find_command(args[0]));
				fprintf(stderr, "args[0] = %s\n args[1] = %s\n", args[0], args[1]);

				execve(find_command(args[0]), args, environ);
				perror("execve");// エラーが発生した場合のメッセージを表示
				free(args);
					exit(1);
			}
			else if (pid > 0)

				keep_fd_update(fds, &keep_fd, i, num_com);
			i++;
		}
		// printf("after -----> tmp->token %s\n", tmp_token->token);
		fprintf(stderr, "hogehogehoge--------------->%s\n", tmp_token->token);
		tmp_token = token_not_pipe_count(tmp_token);
	}
	i = 0;
	while (i < num_com)
	{
		wait(NULL);
		i++;
	}
}