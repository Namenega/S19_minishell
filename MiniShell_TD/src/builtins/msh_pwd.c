/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:41:21 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/04 19:54:18 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/param.h>
#include "minishell.h"
#include "utils.h"


//* BASH
/*
** >unset PWD
** >pwd
** affiche pwd !!
** >echo $PWD
** PWD doesnt exist??
*/

void	msh_pwd(char **env, t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	j = 4;
	(void)msh;
	if (!env)
		return ;				//!Error need a change
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD", 3))
			break ;
		i++;
	}
	if (env[i])
	{
		ft_putstr_fd(&env[i][j], 1);
		write(1, "\n", 1);
	}
	// utils_free_tab(env);
	// return(EXIT_SUCCESS);
}