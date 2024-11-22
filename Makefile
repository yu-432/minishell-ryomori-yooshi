NAME		= minishell

SRCS		=	src/main.c \
				\
				src/init/init_shell.c src/init/env_utils.c src/init/add_env.c \
				\
				src/lexer/lexer.c src/lexer/tokenizer.c src/lexer/tokenize_utils1.c \
				src/lexer/tokenize_utils2.c src/lexer/expand.c \
				src/lexer/expand_utils1.c src/lexer/expand_utils2.c src/lexer/find_syntax_error.c\
				\
				src/execution/run_command.c src/execution/run_command_utils.c src/execution/single_command.c \
				src/execution/multi_command.c src/execution/multi_command_process.c src/execution/execute.c \
				src/execution/execute_utils1.c src/execution/execute_utils2.c src/execution/execute_free.c \
				src/execution/node.c src/execution/node_utils.c src/execution/redirect.c src/execution/redirect_interpret.c \
				src/execution/heredoc.c src/execution/fd_manager1.c src/execution/fd_manager2.c \
				src/execution/set_exit_status.c src/execution/wrapper.c src/execution/heredoc_utils.c\
				\
				src/builtin_func/builtin_cd.c src/builtin_func/builtin_cd_utils.c src/builtin_func/builtin_echo.c \
				src/builtin_func/builtin_env.c src/builtin_func/builtin_exit.c src/builtin_func/builtin_exit_utils1.c \
				src/builtin_func/builtin_exit_utils2.c src/builtin_func/builtin_export.c \
				src/builtin_func/builtin_pwd.c src/builtin_func/builtin_unset.c src/builtin_func/builtin_export_utils.c\
				\
				src/print/put_error1.c src/print/put_error2.c src/print/put_error3.c src/print/put_error4.c \
				\
				src/signal/signal.c src/signal/signal_handler.c

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
