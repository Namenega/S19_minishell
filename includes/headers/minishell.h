/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:47:37 by pyg               #+#    #+#             */
/*   Updated: 2021/08/16 17:27:56 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

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


/*
** READLINE_C
*/

char	*ms_readline(void);
char	**ms_splitline(char *line);


/*
** LAUNCH_C
*/

int		ms_execute(char **args);
int		ms_launch(char **args);


/*
** LAUNCH_C
*/

int ms_num_builtins();
int	ms_cd(char **args);
int ms_help(char **args);
int	ms_exit(char **args);

#endif
