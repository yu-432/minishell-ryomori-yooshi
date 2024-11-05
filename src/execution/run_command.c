#include "../../header/execution.h"
#include "../../header/standard.h"
#include "../../header/condition.h"
#include "../../header/token.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"

char **molding_argv(t_node *node)
{
	char **res;
	int count;
	int i;
	int j;

	count = count_cmd_arg(node);
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (is_not_redirect(node->argv[j]))
			res[i++] = node->argv[j];
		else
			j++;
		j++;
	}
	return (res);
}

int count_pipe(t_node *node)
{
	int count;

	count = 0;
	while (node)
	{
		if (get_token_kind(node->argv[0]) == TOKEN_PIPE)
			count++;
		node = node->next;
	}
	return (count);
}

bool init_exec_info(t_exec_info *info, t_node *node)
{
	ft_memset(info, 0, sizeof(t_exec_info));
	info->keep_fd = -2;
	info->pipe_count = count_pipe(node);
	info->pid = ft_calloc(info->pipe_count + 1, sizeof(pid_t));
	if (!info->pid)
		return (false);
	return (true);
}

bool exec_command(t_condition *condition, t_node *node)
{
	t_node *current;
	t_exec_info info;

	if (node->next == NULL && node->argv[0] != NULL)
		return(execute_single_command(condition, node), true);
	current = node;
	if (!init_exec_info(&info, node))
		return (false);
	while (current->next)
	{
		if(current->kind == NODE_CMD)
			if(!execute_pipeline_cmd(condition, current, &info))
				return (false);
		current = current->next;
	}
	return (execute_last_pipeline_cmd(condition, current, &info));
}

bool run_command(t_condition *condition, t_token *token_list)
{
	t_node *node;

	node = make_node(token_list);//TOEKN_WORDのみでargvを作成
	if (node == NULL)
		return (false);

	// t_node *temp = node;//////////////////////////確認用
	// while(temp)
	// {
	// 	printf("-------------------------\n");
	// 	printf("redirect in = %d, redirect out = %d\n", temp->fd_in, temp->fd_out);
	// 	printf("heredoc_str = %s\n", temp->heredoc_str);
	// 	for (int i = 0; temp->argv[i]; i++)
	// 		printf("argv[%d] = %s\n", i, temp->argv[i]);
	// 	temp = temp->next;
	// 	printf("-------------------------\n");
	// }
	exec_command(condition, node);
	(void)condition;//free token_list
	return (true);
}