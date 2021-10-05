/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:49:19 by namenega          #+#    #+#             */
/*   Updated: 2021/10/05 11:33:32 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

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

int	which_cmd(t_msh *msh, t_exec *exec)
{
	maj_into_min(exec->tab[0]);
	if (!ft_strncmp(exec->tab[0], "echo", 5))
	{
		msh_echo(msh, exec);
		// simple_redirection(msh, exec);
	}
	else if (!ft_strncmp(exec->tab[0], "cd", 3))
		msh_cd(msh, exec);
	else if (!ft_strncmp(exec->tab[0], "unset", 6))
		msh_unset(msh, exec);
	else if (!ft_strncmp(exec->tab[0], "env", 4))
		msh_env(msh, exec);
	else if (!ft_strncmp(exec->tab[0], "pwd", 4))
		msh_pwd(msh, exec);
	else if (!ft_strncmp(exec->tab[0], "export", 4))
		msh_export(exec);
	else
	{
		exec->cmdpath = get_bin(msh, exec->tab[0]);
		simple_redirection(msh, exec);
	}
	// simple_redirection(msh, exec);
	return (EXIT_SUCCESS);
}
