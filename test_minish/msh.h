/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:37:45 by namenega          #+#    #+#             */
/*   Updated: 2021/08/17 15:37:57 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes/libft/libft.h"

# define MS_BUFFER 1024
# define MS_TOK_SIZE 64
# define MS_TOK_DELIM " \t\r\n\a"

typedef struct s_ms
{
	int	i;
}				t_ms;

/*
** MAIN_C
*/

int		main(int ac, char **av, char **envp);
void	ms_loop(void);
char	**ms_splitline(char *line);
void	cmd(char *line);


void	echo(char *line);
// /*
// ** READLINE_C
// */

// char	*ms_readline(void);
// char	**ms_splitline(char *line);


// /*
// ** LAUNCH_C
// */

// int		ms_execute(char **args);
// int		ms_launch(char **args);


// /*
// ** LAUNCH_C
// */

// int ms_num_builtins();
// int	ms_cd(char **args);
// int ms_help(char **args);
// int	ms_exit(char **args);

#endif
