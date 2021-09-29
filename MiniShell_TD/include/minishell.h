/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:45:02 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/29 17:41:16 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include "parser.h"

# define ERR_NO_CMD	"msh: %s: command not found\n"

typedef struct s_msh
{
	char	**env;
	char	**path;
	char	*line;
	t_tok	*tok;
	t_ast	*ast;
	char	ret[4];
	size_t	env_size;
	size_t	env_left;
}				t_msh;

void	set_path(t_msh *msh);
char	*get_bin(t_msh *msh, char *name);

/*
** FILE: words_in_tab.c
*/

t_launch	*get_word_in_tab(t_ast *cmd);

/*
** FILE: io_list.c
*/

void	get_io(t_launch *launch, t_ast *cmd); //TODO:! Adapt to CST changes
t_io	*io_lst_new(t_ast *cmd);
void	io_lst_print(t_io *lst);

#endif
