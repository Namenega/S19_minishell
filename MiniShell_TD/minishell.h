/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:45:02 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/29 12:52:17 by tderwedu         ###   ########.fr       */
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

void	set_path(t_msh *msh);
char	*get_bin(t_msh *msh, char *name);

#endif
