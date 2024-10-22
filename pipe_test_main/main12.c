#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

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

extern char **environ;


typedef struct s_token
{
	char			*token;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

t_token *create_token(char *str, t_token_kind kind);
void	com_token_pipe(t_token *token, int num_com);

// 例10: テキストファイルを一行ずつ逆順に並べ替えて保存
int main()
{
	t_token *token1 = create_token("tac", TOKEN_WORD);
	t_token *token2 = create_token("<", TOKEN_REDIRECT_IN);
	t_token *token3 = create_token("file.txt", TOKEN_WORD);

	t_token *token4 = create_token("|", TOKEN_PIPE);
	t_token *token5 = create_token("sort", TOKEN_WORD);

	t_token *token6 = create_token("|", TOKEN_PIPE);
	t_token *token7 = create_token("uniq", TOKEN_WORD);

	t_token *token8 = create_token(">", TOKEN_REDIRECT_OUT);
	t_token *token9 = create_token("reversed_sorted.txt", TOKEN_WORD);

	token1->next = token2;
	token2->next = token3;
	token3->next = token4;
	token4->next = token5;
	token5->next = token6;
	token6->next = token7;
	token7->next = token8;
	token8->next = token9;

	com_token_pipe(token1, 3);

	return(0);
}
