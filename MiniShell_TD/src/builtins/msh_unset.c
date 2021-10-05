/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:46:24 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 11:32:45 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

//TODO: exit(), CTRL-D

static void	find_env(char *s, char **env, int len)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], s, len) && env[i][len] == '=')
			break ;
		i++;
	}
	free(env[i]);
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
}

int	msh_unset(t_msh *msh, t_exec *exec) //TODO: correct return
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	(void)msh;
	if (!exec->env || !exec->tab[i])
		return (EXIT_FAILURE);				//!Error need a change
	if (exec->tab[i])
		len = ft_strlen(exec->tab[i]);
	while (exec->tab[i])
	{
		find_env(exec->tab[i], exec->env, len);
		i++;
	}
	return (EXIT_SUCCESS);
}
