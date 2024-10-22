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


// 例5: 複数のファイルを結合し、重複行を削除して新しいファイルに保存
int main()
{
	t_token *token1 = create_token("ls", TOKEN_WORD);
	t_token *token2 = create_token("-l", TOKEN_WORD);

	t_token *token3 = create_token("|", TOKEN_PIPE);
	t_token *token4 = create_token("grep", TOKEN_WORD);
	t_token *token5 = create_token("test", TOKEN_WORD);

	t_token *token6 = create_token("|", TOKEN_PIPE);
	t_token *token7 = create_token("tee", TOKEN_WORD);
	t_token *token8 = create_token("output.txt", TOKEN_WORD);

	t_token *token9 = create_token("|", TOKEN_PIPE);
	t_token *token10 = create_token("wc", TOKEN_WORD);
	t_token *token11 = create_token("-l", TOKEN_WORD);

	token1->next = token2;
	token2->next = token3;
	token3->next = token4;
	token4->next = token5;
	token5->next = token6;
	token6->next = token7;
	token7->next = token8;
	token8->next = token9;
	token9->next = token10;
	token10->next = token11;

	com_token_pipe(token1, 4);

	return(0);
}

