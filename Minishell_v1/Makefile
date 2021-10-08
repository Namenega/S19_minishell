# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 15:59:03 by tderwedu          #+#    #+#              #
#    Updated: 2021/10/08 15:05:10 by tderwedu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================ VARIABLES ================================= #

NAME	= minishell

LIBFT	= ./libft
RDLINE	= /Users/$(USER)/.brew/opt/readline

SRC		=	./src/launcher/is_builtin.c \
			./src/launcher/get_cmd_path.c \
			./src/launcher/redirection.c \
			./src/launcher/prep_cmd_utils.c \
			./src/launcher/word_count.c \
			./src/launcher/heredoc.c \
			./src/launcher/launcher_simple.c \
			./src/launcher/launcher_pipe.c \
			./src/launcher/prep_cmd.c \
			./src/launcher/launcher.c \
			./src/parsing/parser2.c \
			./src/parsing/lexer1.c \
			./src/parsing/word_expansion1.c \
			./src/parsing/lexer2.c \
			./src/parsing/parser3.c \
			./src/parsing/parser1.c \
			./src/parsing/heredoc_lst.c \
			./src/parsing/word_expansion2.c \
			./src/builtins/msh_export.c \
			./src/builtins/msh_cd.c \
			./src/builtins/msh_cd_export.c \
			./src/builtins/msh_env.c \
			./src/builtins/msh_pwd.c \
			./src/builtins/msh_echo.c \
			./src/builtins/msh_exit.c \
			./src/builtins/msh_unset.c \
			./src/utils/ret_casting.c \
			./src/utils/path_join.c \
			./src/utils/canonpath.c \
			./src/utils/sort_env.c \
			./src/utils/env_utils.c \
			./src/utils/tab_utils.c \
			./src/utils/msh_getenv.c \
			./src/utils/print_error.c \
			./src/signals/signals.c \
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
