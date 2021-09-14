SRCNAME 	=	./main.c	\
				./echo.c	\
				./tok_recon.c	\
				./utils_0.c		\
				./ft_lst.c

SRCS 		= ${SRCNAME}

OBJS 		= ${SRCS:.c=.o}

NAME		= minishell

CC 			= gcc -g3 #-fsanitize=address
RM 			= rm -f
CFLAGS 		= -Wall -Wextra -Werror -I -I../includes/libft \
				-I /Users/$(USER)/.brew/opt/readline/include

CGREEN		= \033[38;2;0;153;0m
CRED		= \033[0;31m
CYELLOW		= \033[0;33m
CGREY		= \033[38;2;128;128;128m
CEND		= \033[0m


.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		@echo
		@echo "$(CYELLOW)Compilation of Libft$(CEND)"
		@echo "$(CGREY)"
		make -C ../includes/libft
		@echo
		${CC} -o ${NAME} ${OBJS} -L../includes/libft -lft -lreadline -L /Users/$(USER)/.brew/opt/readline/lib 
		@echo "$(CEND)"
		@echo "$(CGREEN)Compilation done !$(CEND)"
		@echo

all:		${NAME}

clean:
		@echo
		@echo "$(CYELLOW)Deleting .o files$(CEND)"
		@echo "$(CGREY)"
		make -C ../includes/libft clean
		${RM} ${OBJS}
		@echo "$(CEND)"
		@echo "$(CGREEN)Deleting done !$(CEND)"
		@echo
		@echo

fclean:		clean
		@echo "$(CYELLOW)Deleting .o files, libft.a and minishell$(CEND)"
		@echo "$(CGREY)"
		${RM} ${NAME} ../includes/libft/libft.a
		@echo "$(CEND)"
		@echo "$(CGREEN)Deleting done !$(CEND)"
		@echo
		@echo

re: 		fclean all

c: 			all clean

.PHONY: 	clean fclean all re