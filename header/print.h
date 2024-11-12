#ifndef PRINT_H
# define PRINT_H

void put_error(char *str);
void put_syntax_error(char *str);
void	put_cd_error(t_condition *cond, char *str, char *perr);
void	export_error(t_condition *cond, char *str, char *perr);
#endif
