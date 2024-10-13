#include "../../header/lexer.h"
#include "../../header/token.h"

bool i

void find_command_path(t_condition *condition, t_token *tokenized)
{
	bool is_command;

	is_command = true;
	while (tokenized)
	[
		if(tokenized->kind == TOKEN_WORD && is_command)
		{

		}
		else if (tokenized->kind == TOKEN_PIPE)
		{
			is_command = true;
		}
	]
}