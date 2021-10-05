/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:42:37 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 16:53:56 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

static void	handle_io(t_exec *exec)
{
	int		fd;
	int		err_d;
	t_io	*io;

	io = exec->io;
	while (io)
	{
		if (io->heredoc_fd <= 0)
		{
			fd = open(io->filename, io->oflag, 0644);
			if (fd == -1)
				return ;				//! Error msg need a change
			err_d = dup2(fd, io->fd);
			if (err_d == -1)
				return ;				//! Error msg need a change.
		}
		else
		{
			err_d = dup2(io->heredoc_fd, io->fd);
			if (err_d == -1)
				return ;				//! Error msg need a change.
		}
		io = io->next;
	}
}

void	handle_redirection(t_exec *exec)
{
	int		err_d;

	if (exec->pipe_in[0] >= 0)
	{
		close(exec->pipe_in[1]);
		err_d = dup2(stdin, exec->pipe_in[0]);
		if (err_d == -1)
			return ;				//! Error msg need a change.
	}
	if (exec->pipe_out[1] >= 0)
	{
		close(exec->pipe_out[0]);
		err_d = dup2(stdin, exec->pipe_out[1]);
		if (err_d == -1)
			return ;				//! Error msg need a change.
	}
	handle_io(exec);
}