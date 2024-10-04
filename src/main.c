#include "../header/condition.h"
#include "../header/init.h"

int main(int argc, char **argv, char **envp)
{
	t_condition condition;
	
	printf("test\n");
	init_shell(&condition, argv, envp);
}