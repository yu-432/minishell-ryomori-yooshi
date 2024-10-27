NAME		= minishell

SRCS		= 	src/main.c \
				src/environ/env_util.c src/environ/add_env.c \
				src/init/init_shell.c \
				src/lexer/lexer.c src/lexer/tokenize_util.c src/lexer/tokenizer.c src/lexer/expand.c src/lexer/expand_dollar.c \
				src/lexer/find_syntax_error.c \
				src/execution/pipe.c

OBJS		= ${SRCS:.c=.o}

LIBFT		= libft/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

AR			= ar rcs

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libft
			${CC} ${OBJS} $(LIBFT) -lreadline -o ${NAME}

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
			${RM} ${OBJS}
			${MAKE} -C libft clean

fclean:		clean
			${RM} ${NAME}
			${MAKE} -C libft fclean

re:			fclean all

.PHONY:		all clean fclean re bonus


#######################
# Debug : make debug
#######################
.PHONY: minishell
debug:
	gcc pipe.c -lreadline -o minishell && ./minishell 2>/dev/null
debug-print:
	gcc pipe.c -lreadline -o minishell && ./minishell