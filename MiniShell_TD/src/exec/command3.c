/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:55:18 by namenega          #+#    #+#             */
/*   Updated: 2021/09/30 13:57:48 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	simple_redirection(t_io *io, t_exec *ex)
{
	pid_t	pid;
	int		entry_file;


	pid = fork();
	if (pid < 0)
		return ;					//! Error msg need a change
	if (pid == 0)
	{
		entry_file = open(io->filename, io->oflag, 0644);
		if (entry_file == -1)
			return ;				//! Error msg need a change
		dup2(entry_file, io->fd);
		execve(ex->cmdpath, ex->tab, ex->env);
		close(entry_file);
	}
}
