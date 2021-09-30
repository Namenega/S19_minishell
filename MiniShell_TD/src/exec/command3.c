/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:55:18 by namenega          #+#    #+#             */
/*   Updated: 2021/09/30 14:05:57 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	simple_redirection(t_msh *msh, t_exec *ex)
{
	t_io	*io;
	pid_t	pid;
	int		entry_file;


	pid = fork();
	if (pid < 0)
		return ;					//! Error msg need a change
	if (pid == 0)
	{
		io = ex->io;
		while (io)
		{
			entry_file = open(io->filename, io->oflag, 0644);
			if (entry_file == -1)
				return ;				//! Error msg need a change
			dup2(entry_file, io->fd);
			io = io->next;
		}
		msh->env = NULL;
		msh_free(msh);
		execve(ex->cmdpath, ex->tab, ex->env);
		// gestion error execve
		close(entry_file);
		
	}
}
