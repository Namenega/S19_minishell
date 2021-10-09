/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:02:42 by namenega          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/09 12:29:48 by namenega         ###   ########.fr       */
=======
/*   Updated: 2021/10/09 12:43:30 by tderwedu         ###   ########.fr       */
>>>>>>> b994d50c41001aa1327e7e1fe5a7ab2602d6818c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

pid_t	g_sig = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (g_sig == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		kill(g_sig, SIGKILL);
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT && g_sig != 0)
	{
		if (!kill(g_sig, SIGCONT))
			write(1, "Quit: 3\n", 8);
	}
}

void	signal_handling(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
