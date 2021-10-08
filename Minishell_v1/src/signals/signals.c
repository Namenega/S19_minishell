/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:02:42 by namenega          #+#    #+#             */
/*   Updated: 2021/10/08 16:26:30 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

pid_t	g_sig = 0;

void	handle_sigint(int sig)
{
	printf("\n");
	if (sig == SIGINT && g_sig == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// else if (sig == SIGINT && g_sig != 0)
	// {
	// 	kill(g_sig, SIGCONT);
	// }
}

void	handle_sigusr1(int sig)
{
	if (sig == SIGUSR1)
	{
		close(STDIN_FILENO);
		write(STDOUT_FILENO, "exit\n", 1);
		exit(EXIT_SUCCESS);
	}
}

void	signal_handling(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGUSR1, handle_sigusr1);
	signal(SIGQUIT, SIG_IGN);
}
