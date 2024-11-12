#ifndef PRINT_H
# define PRINT_H

void put_error(char *str);
void put_syntax_error(char *str);
void	put_cd_error(t_condition *cond, char *str, char *perr);
void	put_export_error(t_condition *condition, char *argv);
void	export_error(t_condition *cond, char *str, char *perr);
int	tma_error_check(t_condition *condition, char **args);
void	numeric_argument_error(char *argment);
#endif
