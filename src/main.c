#include "../header/condition.h"
#include "../header/standard.h"
#include "../header/init.h"

int main(int argc, char **argv, char **envp)
{
	t_condition condition;

	(void)argc;
	init_shell(&condition, argv, envp);
	// t_item *test;//check environ t_item
	// test = condition.environ;
	// while(test) 
	// {
	// 	printf("%s = %s\n", test->key, test->value);
	// 	test = test->next;
	// }
}