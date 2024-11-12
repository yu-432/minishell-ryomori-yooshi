#include "../../header/standard.h"

bool is_space(char c)
{
	return(c == ' ' || c == '\t' || c == '\n');
}

bool is_metacharacter(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '(' || c == ')' \
			|| c == '<' || c =='>' || c == ' ' || c == '\t' || c == '\n');
}

bool is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
