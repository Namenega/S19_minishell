/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:23:31 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/09 12:10:22 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

extern pid_t	g_sig;

void	launcher(t_msh *msh)
{
	t_exec	exec;

	if (!msh->ast)
		return ;
	exec.msh = msh;
	exec.cmdpath = NULL;
	no_pipe(exec.pipe_in);
	no_pipe(exec.pipe_out);
	if (msh->ast->type == AST_PIPE)
		launch_pipe_seq(&exec);
	else
		launch_simple_cmd(&exec);
	msh->ast = free_ast(msh->ast);
	g_sig = 0;
}

void	error_exec(t_exec *exec, int ret)
{
	free_exec(exec);
	free_msh(exec->msh);
	exit(ret);
}

void	error_exec_errno(t_exec *exec, char *msg)
{
	print_error(msg, strerror(errno), "\n", errno);
	free_exec(exec);
	free_msh(exec->msh);
	exit(errno);
}
