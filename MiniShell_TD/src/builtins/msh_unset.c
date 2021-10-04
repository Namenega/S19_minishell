/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:46:24 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/04 18:31:49 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// 'unset VAR' et non 'unset $VAR'
//if unset + rien -> affiche/ne fait rien

/*
**if (!ft_strncmp(exec->tab[0], "unset", 6))
**	msh_unset()
*/

//TODO: exit(), CTRL-D

static void	find_env(char *s, char **env, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], s, len))
		{
			printf("--env[i] = [%s]\n", env[i]);
			// tmp = env[i];
			// del_env(tmp, env);
			break ;
		}
		i++;
	}
	while (env[i] && env[i + 1])
	{
		tmp = env[i];
		env[i] = env[i + 1];
		env[i + 1] = tmp;
		i++;
	}
	tmp = env[i];
	printf("env[i] = [%s]\n", env[i]);
	env[i] = NULL;
	printf("-env[i] = [%s]\n", env[i]);
}

void	msh_unset(char **env, t_exec *exec)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	if (!env || !exec->tab[i])
		return ;				//!Error need a change
	if (exec->tab[i])
		len = ft_strlen(exec->tab[i]);
	while (exec->tab[i])
	{
		find_env(exec->tab[i], env, len);
		i++;
	}
}
