/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:42:37 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/09 12:10:22 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

void	reverse_redir(t_exec *exec)
{
	t_io	*io;
	int		err_d;

	io = exec->io;
	while (io)
	{
		close(io->fd_h);
		err_d = dup2(io->fd_d, io->fd);
		if (err_d == -1)
			error_exec_errno(exec, MSG_DUP2);
		io = io->next;
	}
}

void	redir_io_lst(t_exec *exec, t_io *io, int save)
{
	int		err_d;

	while (io)
	{
		if (io->fd_h <= 0)
		{
			io->fd_h = open(io->filename, io->oflag, 0644);
			if (io->fd_h == -1)
				error_exec_errno(exec, MSG_OPEN);
			free(io->filename);
			io->filename = NULL;
		}
		if (save)
		{
			io->fd_d = dup(io->fd);
			if (io->fd_d == -1)
				error_exec_errno(exec, MSG_DUP);
		}
		err_d = dup2(io->fd_h, io->fd);
		if (err_d == -1)
			error_exec_errno(exec, MSG_DUP2);
		io = io->next;
	}
}

void	apply_redir(t_exec *exec, int save)
{
	int		err_d;

	if (exec->pipe_in[0] >= 0)
	{
		close(exec->pipe_in[1]);
		err_d = dup2(exec->pipe_in[0], 0);
		if (err_d == -1)
			error_exec_errno(exec, MSG_DUP2);
	}
	if (exec->pipe_out[1] >= 0)
	{
		close(exec->pipe_out[0]);
		err_d = dup2(exec->pipe_out[1], 1);
		if (err_d == -1)
			error_exec_errno(exec, MSG_DUP2);
	}
	redir_io_lst(exec, exec->io, save);
}
