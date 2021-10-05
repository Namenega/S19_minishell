/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:55:18 by namenega          #+#    #+#             */
/*   Updated: 2021/10/05 15:34:40 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include "../../include/exec.h"

void	list_redirection(t_exec *exec, int entry_file)
{
	t_io	*io;
	int		err_d;

	io = exec->io;
	while (io)
	{
		if (io->heredoc_fd <= 0)
		{
			entry_file = open(io->filename, io->oflag, 0644);
			if (entry_file == -1)
				return ;				//! Error msg need a change
			err_d = dup2(entry_file, io->fd);
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
	// return (entry_file);
}

void	simple_redirection(t_msh *msh, t_exec *ex)
{
	pid_t	pid;
	int		entry_file;
	int		ret;

	entry_file = 0;
	pid = fork();
	if (pid < 0)
		return ;					//! Error msg need a change
	if (pid == 0)
	{
		list_redirection(ex, entry_file);
		msh->env = NULL;
		msh_free(msh);
		execve(ex->cmdpath, ex->tab, ex->env);
		// gestion error execve
		close(entry_file);
		if (ex->cmdpath)
			free(ex->cmdpath);
		if (ex->tab)
			ft_free_split(ex->tab);
	}
	waitpid(pid, &ret, 0);
}

void	exec_error(t_exec *exec, char *msg)//TODO: code
{
	(void)exec;
	(void)msg;
}
