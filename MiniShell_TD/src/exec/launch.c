/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:23:31 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 17:28:13 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

static void	msh_no_pipe(int	pipe[2])
{
	pipe[0] = -1;
	pipe[1] = -1;
}

static void	msh_close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
	msh_no_pipe(pipe[2]);
}

static void	msh_switch_pipe(int pipe_in[2], int pipe_out[2])
{
	msh_close_pipe(pipe_in);
	pipe_in[0] = pipe_out[0];
	pipe_in[1] = pipe_out[1];
}

void	msh_launch_all(t_msh *msh)
{
	t_exec	exec;

	msh_no_pipe(exec.pipe_in);
	msh_no_pipe(exec.pipe_out);
	if (msh->ast->type == AST_PIPE)
		msh_launch_pipe(msh, &exec);
	else
		msh_launch_one(msh, &exec);
}
/*
**	USE DUP(1) TO SACE A COPY !!!
*/

void	msh_launch_pipe(t_msh *msh, t_exec *exec)
{
	int		ret;
	t_ast	*cmd;

	cmd = msh->ast;
	msh_no_pipe(exec->pipe_in);
	while (cmd)
	{
		cmd_get(&msh, cmd->left, &exec);
		cmd = cmd->right;
		if (pipe(exec->pipe_out) == -1)
			return ; // TODO: ERROR HANDLING
		msh_launch_one(msh, &exec);
		msh_switch_pipe(exec->pipe_in, exec->pipe_out);
	}
	msh_close_pipe(exec->pipe_in);
	waitpid(exec.pid, &ret, 0); // TODO: TODO
}

void	msh_launch_one(t_msh *msh, t_exec *exec)
{
	int		ret;
	pid_t	pid;

	ret = launch_builtin(msh, exec);
	if (ret >= 0)
		return ;
	pid = fork();
	if (pid < 0)
		return ;					//! Error msg need a change
	if (pid == 0)
	{
		handle_redirection(exec);
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
}