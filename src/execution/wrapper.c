#include "../../header/token.h"
#include "../../header/node.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"

void wrap_close(int fd)
{
	if (fd != -1 && close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
}

void wrap_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit(1);
	}
}