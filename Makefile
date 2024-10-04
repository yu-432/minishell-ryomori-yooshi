NAME		= minishell

SRCS		= 	src/main.c \
				src/environ/add_env.c \
				src/init/init_shell.c

OBJS		= ${SRCS:.c=.o}

LIBFT		= libft/libft.a

CC			= cc
# CFLAGS		= -Wall -Wextra -Werror

AR			= ar rcs

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libft
			${CC} ${OBJS} $(LIBFT) -o ${NAME}

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
