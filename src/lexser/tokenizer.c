#include "../../header/lexser.h"
#include "../../header/token.h"
#include "../../libft/libft.h"

t_token *tokenizer(char *line)
{
	t_token head;

	ft_memset(&head, 0, sizeof(t_token));
	while (*line)
	{
		if (is_space(*line))
			*line++;
		
	}
}