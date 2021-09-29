/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:45:02 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/29 15:19:59 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include "lexer.h"
# include "parser.h"
# include "word_expansion.h"

# define ERR_NO_CMD	"msh: %s: command not found\n"

typedef struct s_tok	t_tok;
typedef struct s_cst	t_cst;
typedef struct s_msh	t_msh;

typedef struct s_msh
{
	char	**env;
	char	**path;
	char	*line;
	t_tok	*head;
	t_cst	*root;
	char	ret[4];
	size_t	env_size;
	size_t	env_left;
}				t_msh;

typedef struct s_io
{
	int				fd;
	int				oflag;
	char			*filename;
	struct s_io	*next;
}				t_io;

typedef struct s_launch
{
	int			size;
	char		**tab;
	char		**env;
	t_io		*io;
	t_io		*last;
	// t_fd		*pipe_in;
	// t_fd		*pipe_out;
}				t_launch;

void	set_path(t_msh *msh);
char	*get_bin(t_msh *msh, char *name);

/*
** FILE: words_in_tab.c
*/

t_launch	*get_word_in_tab(t_cst *cmd);

/*
** FILE: io_list.c
*/

void	get_io(t_launch *launch, t_cst *cmd); //TODO:! Adapt to CST changes
// void	get_io_args(t_launch *launch, t_cst *cmd);
// void	io_lst_new_addback(t_cst *cmd, t_io *io);
// t_io	*io_lst_last(t_io *lst);
t_io	*io_lst_new(t_cst *cmd);
// void	io_lst_add_back(t_io **alst, t_io *new);
void	io_lst_print(t_io *lst);

#endif
