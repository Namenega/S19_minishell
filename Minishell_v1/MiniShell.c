/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniShell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:05:03 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 14:18:16 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

/* Global for Signals */

pid_t	g_sig;

t_msh	*free_msh(t_msh *msh)
{
	(void)msh;
	return (NULL);
}

void	msh_error(t_msh *msh, char *msg)
{
	(void)msh;
	printf("\e[31mEXIT_FAILURE\e[0m\n");
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

/*
**	TODO List
** - check free : line, tok, ast, exec
**
*/

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	t_msh	msh;

	if (argc > 1)
	{
		write(2, MSG_ARGC, ft_strlen(MSG_ARGC));
		exit(EXIT_FAILURE);
	}
	g_sig = 0;
	msh.env_left = 5;
	msh.env_size = size_tab(env) + msh.env_left;
	msh.env = grow_tab(env, msh.env_size);
	msh.line = NULL;
	msh.tok = NULL;
	msh.ast = NULL;
	msh.ret[0] = '0';
	msh.ret[1] = '\0';

	printf("Welcome! Exit by pressing CTRL-D.\n");
	msh.cwd = ft_strdup(msh_getenv(env, "PWD", 3));
	signal_handling();
	while(1)
	{
		msh.line = readline("\e[32mmsh>\e[0m");
		if (!msh.line)
			break;
		else if (*msh.line)
		{
			add_history(msh.line);
			lexer(&msh);
			parser(&msh);
			we_word_expansion(&msh);
			// if (exec == NULL)
			// {
			// 	g_sig == 0;
			// }
			// handle_heredoc()&msh;
			launcher(&msh);
		}
		g_sig = 0;
	}
	printf("\e[31m \nBye Bye!\e[0m\n");
}
