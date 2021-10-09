/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:38:08 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/09 12:23:14 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

extern pid_t	g_sig;

static inline void	launch_in_subshell(t_exec *exec)
{
	char	**env;

	apply_redir(exec, 0);
	if (!*exec->argv)
		error_exec(exec, EXIT_SUCCESS);
	if (!exec->cmdpath)
	{
		print_error(MSG_MSH, exec->argv[0], ERR_NOTFOUND, 0);
		error_exec(exec, ERRNO_NOT_FOUND);
	}
	env = exec->msh->env;
	exec->msh->env = NULL;
	free_msh(exec->msh);
	free_io(exec->io);
	execve(exec->cmdpath, exec->argv, env);
	error_exec_errno(exec, MSG_EXECVE);
}

void	launch_simple_cmd(t_exec *exec)
{
	int	ret;

	prep_next_cmd(exec->msh, exec->msh->ast, exec);
	errno = 0;
	if (exec->fct)
	{
		apply_redir(exec, 1);
		ret = (*exec->fct)(exec);
		reverse_redir(exec);
	}
	else
	{
		g_sig = fork();
		if (g_sig < 0)
			error_exec_errno(exec, MSG_FORK);
		if (g_sig == 0)
			launch_in_subshell(exec);
		waitpid(g_sig, &ret, 0);
		if (WIFSIGNALED(ret))
			ret = 128 + WTERMSIG(ret);
		else
			ret = WEXITSTATUS(ret);
	}
	ret_itoa(exec->msh, ret);
	free_exec(exec);
}
