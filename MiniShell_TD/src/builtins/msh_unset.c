/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:46:24 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 08:51:21 by tderwedu         ###   ########.fr       */
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

	tmp = NULL;


	// i = 0;
	// printf("--------------\n");
	// printf("[BEFORE]]\n");
	// while (env[i])
	// {
	// 	printf("-env[i] = [%s]\n", env[i]);
	// 	i++;
	// }
	// printf("\n\n\n\n");





	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], s, len))
			break ;
		i++;
	}
	// printf("i = %d\n", i);
	// printf("VAR : -env[i] = [%s]\n", env[i]);
	while (env[i] && env[i + 1])
	{
		tmp = env[i];
		env[i] = env[i + 1];
		env[i + 1] = tmp;
		i++;
	}
	// printf("i = %d\n", i);
	env[i] = NULL;



	// printf("\n\n\n\n");
	// printf("--------------\n");
	// printf("[AFTER]]\n");
	// i = 0;
	// while (env[i])
	// {
	// 	printf("-env[i] = [%s]\n", env[i]);
	// 	i++;
	// }
}

int	msh_unset(t_msh *msh, t_exec *exec)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	if (!exec->env || !exec->tab[i])
		return ;				//!Error need a change
	if (exec->tab[i])
		len = ft_strlen(exec->tab[i]);
	while (exec->tab[i])
	{
		find_env(exec->tab[i], exec->env, len);
		i++;
	}
}
