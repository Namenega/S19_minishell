/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:49:19 by namenega          #+#    #+#             */
/*   Updated: 2021/10/05 09:12:23 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static char	*maj_into_min(t_msh *msh, t_exec *exec)
{
	int		i;
	char	*s;

	s = ft_strdup(exec->tab[0]);
	if (!s) //TODO: correct error handling
		msh_error(msh, ERR_MALLOC);
	i = 0;
	while (s[i])
	{
		s[i] = (s[i] & ~0x20);
		// if (s[i] >= 'A' && s[i] <= 'Z')
		// 	s[i] += 32; // 0x20
		i++;
	}
	return (s);
}

int	which_cmd(t_msh *msh, t_exec *exec)
{
	char	*cmd;

	cmd = maj_into_min(msh, exec->tab[0]);
	// printf("2.tab[0] = [%s]\n", exec->tab[0]);
	if (!ft_strncmp(cmd, "echo", 5))
		msh_echo(msh, exec);
	else if (!ft_strncmp(cmd, "cd", 3))
		msh_cd(msh, exec);
	else if (!ft_strncmp(cmd, "unset", 6))
		msh_unset(msh, exec);
	else if (!ft_strncmp(cmd, "env", 4))
		msh_env(msh, exec);
	else if (!ft_strncmp(cmd, "pwd", 4))
		msh_pwd(msh, exec);
	else
	{
		exec->cmdpath = get_bin(msh, exec->tab[0]);
		simple_redirection(msh, exec);
	}
	free(cmd);
}
