/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:46:24 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/04 19:22:07 by namenega         ###   ########.fr       */
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
