#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/init.h"
#include "../../header/builtin_func.h"

bool	is_envname(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}
