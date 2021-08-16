/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:04:21 by pyg               #+#    #+#             */
/*   Updated: 2021/08/16 17:29:39 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/minishell.h"

int	ms_launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("msh");
	}
	else if (pid < 0)
		perror("msh");
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}
