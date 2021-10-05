/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:49:19 by namenega          #+#    #+#             */
/*   Updated: 2021/10/05 14:09:34 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

#define MSG_BASH		"msh: "
#define MSG_NOTFOUND	": command not found\n"

static void	maj_into_min(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		s[i] = (s[i] | 0x20);
		i++;
	}
}

void	which_cmd(t_msh *msh, t_exec *exec)
{
	int	ret;

	maj_into_min(exec->tab[0]);
	// simple_redirection(msh, exec);
	if (!ft_strncmp(exec->tab[0], "echo", 5))
	{
		ret = msh_echo(msh, exec);
	}
	else if (!ft_strncmp(exec->tab[0], "cd", 3))
		ret = msh_cd(msh, exec);
	else if (!ft_strncmp(exec->tab[0], "unset", 6))
		ret = msh_unset(msh, exec);
	else if (!ft_strncmp(exec->tab[0], "env", 4))
		ret = msh_env(msh, exec);
	else if (!ft_strncmp(exec->tab[0], "pwd", 4))
		ret = msh_pwd(msh, exec);
	else if (!ft_strncmp(exec->tab[0], "export", 4))
		ret = msh_export(exec);
	else
	{
		exec->cmdpath = get_bin(msh, exec->tab[0]);
		if (!exec->cmdpath)
		{
			msh_print_error(MSG_BASH, exec->tab[0], MSG_NOTFOUND, 0);
			ret_int_2_str(msh, EXIT_FAILURE);
			return ;
		}
		simple_redirection(msh, exec);
		ret = EXIT_SUCCESS; //TODO: get return value from subprocess
	}
	// simple_redirection(msh, exec);
	ret_int_2_str(msh, ret);
}
