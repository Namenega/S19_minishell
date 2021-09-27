/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:10_MiniShell/minishell.h
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:45:02 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/24 16:00:37 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_msh	t_msh;

# include "lexer.h"
# include "parser.h"
# include "word_expansion.h"

typedef struct s_msh
{
	char	**env;
	char	*line;
	t_tok	*tokens;
	t_cst	*root;
	char	*ret;
}				t_msh;
=======
/*   launcher.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:41:14 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/24 17:23:30 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHER_H
# define LAUNCHER_H

#include "lexer.h"
#include "parser.h"
#include "word_expansion.h"
#include "minishell.h"

# define ERR_MALLOC		"Malloc error." // TODO: One Header for all msg

typedef struct s_io	t_io;

typedef struct s_exec
{
	int		*pipe_in[2];
	int		*pipe_out[2];
	int		argc;
	char	**argv;
	char	**env;
	t_cst	*cmd_root;
}				t_exec;

typedef struct s_io
{
	int		fd;
	char	*filename;
	int		oflag;
	t_io	*next;
}				t_io;

void	launcher(t_msh *msh);
>>>>>>> c0441df5d3962ebfb1ec197f5bbd1ccbbc6dead7:10_MiniShell/launcher.h

#endif