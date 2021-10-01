# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namenega <namenega@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 15:59:03 by tderwedu          #+#    #+#              #
#    Updated: 2021/10/01 16:34:46 by namenega         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================ VARIABLES ================================= #

NAME	= minishell

LIBFT	= ./libft
RDLINE	= /Users/$(USER)/.brew/opt/readline

SRC		=	./src/builtins/msh_cd.c \
			./src/builtins/msh_echo.c \
			./src/builtins/msh_env.c \
			./src/builtins/msh_exit.c \
			./src/builtins/msh_export.c \
			./src/builtins/msh_pwd.c \
			./src/builtins/msh_unset.c \
			./src/builtins/unset.c \
			./src/exec/command1.c \
			./src/exec/command2.c \
			./src/exec/command3.c \
			./src/exec/heredoc.c \
			./src/parsing/lexer1.c \
			./src/parsing/lexer2.c \
			./src/parsing/parser1.c \
			./src/parsing/parser2.c \
			./src/parsing/parser3.c \
			./src/parsing/word_expansion1.c \
			./src/parsing/word_expansion2.c \
			./src/utils/utils.c \
			./src/utils/utils_cst.c \
			./src/utils/utils_env.c \
			./set_path.c \
			./get_bin.c \
			./MiniShell.c

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

OBJ		= ${SRC:.c=.o}

INCL	= -I ${LIBFT} -I ${RDLINE}/include -I ./include

LIBS	= -L ${LIBFT} -lft -L ${RDLINE}/lib -lreadline

# ================================== RULES =================================== #

%.o:		%.c
			${CC} ${CFLAGS} ${INCL} -c $< -o $@

all:		$(NAME)

$(NAME):	${OBJ}
			make -C ${LIBFT}
			${CC} -o ${NAME} ${OBJ} ${LIBS}

clean:
			rm -f ${OBJ}

fclean:		clean
			rm -f ${NAME}

re:			fclean	all

.phony:		all clean fclean re
