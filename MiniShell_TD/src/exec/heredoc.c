/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 15:24:00 by namenega          #+#    #+#             */
/*   Updated: 2021/10/01 16:33:23 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

//CTRL C need to stop process
//CTRL D need to stop process but print readline buffer already registered.

static void	read_heredoc(char *line, t_exec *exec)
{
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, exec->io->filename))
			break ;
		write(1, line, ft_strlen(line));
		write(1, "\n" ,1);
	}
}

void	heredoc(t_exec *exec)
{
	pid_t	pid;
	int		pipefd[2];
	char	*line;
	int		ret;

	if (pipe(pipefd) == -1)
		return ;					//!Error msg need to change : pipe error.
	pid = fork();
	if (pid < 0)
		return ;					//!Error msg need to change : fork error.
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		read_heredoc(line, exec);
		// while (1)
		// {
		// 	line = readline("> ");
		// 	if (!line || !ft_strcmp(line, exec->io->filename))
		// 		break ;
		// 	write(1, line, ft_strlen(line));
		// 	write(1, "\n" ,1);
		// }
		free(line);
		close(pipefd[1]);
		close(pipefd[0]);
		exit(0);					//! Error need to change
	}
	else
	{
		waitpid(pid, &ret, 0);
		close(pipefd[1]);
		if (ret == EXIT_SUCCESS)
			close(pipefd[0]);
	}
}
