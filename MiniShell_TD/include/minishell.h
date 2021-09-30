/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:45:02 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/30 10:20:17 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>

# include "parser.h"
# include "exec.h"

/* TODO: all ERR in ine header */
# define ERR_NO_CMD	"msh: %s: command not found\n"

typedef struct s_tok	t_tok;
typedef struct s_ast	t_ast;
typedef struct s_msh	t_msh;

struct s_msh
{
	char	**env;
	char	**path;
	char	*line;
	t_tok	*tok;
	t_ast	*ast;
	char	ret[4];
	size_t	env_size;
	size_t	env_left;
};

void	set_path(t_msh *msh);
char	*get_bin(t_msh *msh, char *name);

#endif
