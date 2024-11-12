NAME		= minishell

SRCS		= 	src/main.c \
				src/init/init_shell.c src/init/env_util.c src/init/add_env.c \
				src/lexer/lexer.c src/lexer/tokenize_util.c src/lexer/tokenizer.c src/lexer/expand.c src/lexer/expand_dollar.c \
				src/lexer/find_syntax_error.c\
				src/print/put_error.c src/print/put_error_utils.c\
				src/signal/signal.c \
				src/execution/multi_command.c src/execution/single_command.c src/execution/run_command.c src/execution/execute_helper.c src/execution/process.c src/execution/redirect.c src/execution/execute.c src/execution/fd_manager.c src/execution/heredoc.c src/execution/node_helper.c src/execution/node.c src/execution/wrapper.c src/execution/pipe.c \
				src/builtin_func/builtin_echo.c src/builtin_func/builtin_env.c src/builtin_func/builtin_export.c src/builtin_func/builtin_unset.c src/builtin_func/builtin_cd.c src/builtin_func/builtin_exit.c src/builtin_func/builtin_pwd.c src/builtin_func/builtin_cd_utils.c src/builtin_func/builtin_exit_utils1.c src/builtin_func/builtin_exit_utils2.c \

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
