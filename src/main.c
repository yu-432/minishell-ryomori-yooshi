#include "../header/condition.h"
#include "../header/standard.h"
#include "../header/init.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#define PROMPT "minishell$ "
#define PATH_NAME_SIZE 1024

void read_loop(t_condition *condition)
{
	char *line;

	line = readline(PROMPT);
	if (!line)
	{
		printf("TODO:readline error\n");
		exit(1);
	}
	printf("readline = %s\n", line);//check用
	//TODO:tokenizer->parser
	if (*line == '\0')
		add_history(line);
	free(line);
	(void)condition;
}

// void update_condition(t_condition *condition)
// {
// 	char *cwd_path;
// 	cwd_path = malloc(sizeof(char) * PATH_NAME_SIZE);
// 	if (!cwd_path)
// 	{
// 		printf("TODO:cwd_path malloc failed\n");
// 		exit(1);
// 	}
// 	printf("%s\n", condition->cwd);
// 	condition->cwd = getcwd(cwd_path, PATH_NAME_SIZE);
// 	//signal?
// }

void shell_loop(t_condition *condition)
{
	while (true)
	{
		// update_condition(condition);いるかわからない
		read_loop(condition);
	}
	(void)condition;
	return ;
}

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
	shell_loop(&condition);
}