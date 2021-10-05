/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:49:19 by namenega          #+#    #+#             */
/*   Updated: 2021/10/05 16:56:08 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static inline void	set_lowercase(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		s[i] = (s[i] | 0x20);
		i++;
	}
}

int	launch_builtin(t_msh *msh, t_exec *exec)
{
	int	ret;

	set_lowercase(exec->tab[0]);
	if (!ft_strncmp(exec->tab[0], "echo", 5))
		ret = msh_echo(msh, exec);
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
		ret = -1;
	if (ret >= 0)
		ret_int_2_str(msh, ret);
	return (ret);
}
