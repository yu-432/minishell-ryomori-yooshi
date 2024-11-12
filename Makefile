NAME		= minishell

SRCS		= 	src/main.c \
				src/init/init_shell.c src/init/add_env_util.c src/init/add_env.c \
				src/lexer/lexer.c src/lexer/tokenizer.c \
				src/lexer/expand.c src/lexer/expand_dollar.c src/lexer/expand_dollar_utils.c\
				src/lexer/find_syntax_error.c src/lexer/expand_quote.c \
				src/lexer/tokenize_util1.c src/lexer/tokenize_util2.c\
				src/signal/signal.c \
				src/execution/multi_command.c src/execution/single_command.c \
				src/execution/run_command.c src/execution/run_command_utils.c \
				src/execution/process.c src/execution/redirect.c \
				src/execution/execute.c src/execution/fd_manager1.c src/execution/fd_manager2.c \
				src/execution/execute_utils1.c src/execution/execute_utils2.c \
				src/execution/heredoc.c src/execution/node_utils.c src/execution/node.c \
				src/execution/wrapper.c src/execution/pipe.c src/execution/set_exit_status.c\
				src/builtin_func/builtin_echo.c src/builtin_func/builtin_env.c \
				src/builtin_func/builtin_export.c src/builtin_func/builtin_unset.c \
				src/builtin_func/builtin_cd.c src/builtin_func/builtin_exit.c \
				src/builtin_func/builtin_pwd.c src/builtin_func/builtin_cd_until.c \
				src/builtin_func/builtin_exit_until1.c src/builtin_func/builtin_exit_until2.c \
				src/builtin_func/builtin_export_until.c \
				src/print/put_error.c src/print/put_error2.c


OBJS		= ${SRCS:.c=.o}

LIBFT		= libft/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

AR			= ar rcs

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libft
			${CC} -lreadline ${OBJS} $(LIBFT) -o ${NAME}

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
			${RM} ${OBJS}
			${MAKE} -C libft clean

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFT}

re:			fclean all

.PHONY:		all clean fclean re bonus
