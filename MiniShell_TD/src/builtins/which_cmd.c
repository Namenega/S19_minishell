/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:49:19 by namenega          #+#    #+#             */
/*   Updated: 2021/10/04 19:47:27 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static char	*maj_into_min(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
		i++;
	}
	return (s);
}

void	which_cmd(t_exec *exec, char **env, t_msh *msh)
{
	(void)msh;
	(void)env;
	// printf("1.tab[0] = [%s]\n", exec->tab[0]);
	exec->tab[0] = maj_into_min(exec->tab[0]);
	// printf("2.tab[0] = [%s]\n", exec->tab[0]);
	if (!ft_strncmp(exec->tab[0], "echo", 5))
		msh_echo(msh, exec);
	else if (!ft_strncmp(exec->tab[0], "cd", 3))
		msh_cd(msh, exec);
	else if (!ft_strncmp(exec->tab[0], "unset", 6))
		msh_unset(env, exec);
	else if (!ft_strncmp(exec->tab[0], "env", 4))
		msh_env(msh, exec->tab, env);
	// else if (!ft_strncmp(exec->tab[0], "exit", 5))
	// 	msh_exit();
	// else if (!ft_strncmp(exec->tab[0], "export", 7))
	// 	msh_export();
	else if (!ft_strncmp(exec->tab[0], "pwd", 4))
		msh_pwd(env, msh);
	else
	{
		exec->cmdpath = get_bin(msh, exec->tab[0]);
		simple_redirection(msh, exec);
	}
}
