/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:45:02 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 18:52:13 by namenega         ###   ########.fr       */
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
# include "error_messages.h"

/* TODO: all ERR in ine header */
/*# define ERR_NO_CMD	"msh: %s: command not found\n"*/

/*
** Global for Signals
*/

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
	char	*cwd;
};

void	msh_free(t_msh *msh);

void	set_path(t_msh *msh);
char	*get_bin(t_msh *msh, char *name);

void	signal_handling(void);
void	handle_sigint(int sig);
void	handle_sigusr1(int sig);

#endif
