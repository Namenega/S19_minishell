/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:46:24 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/04 17:19:37 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// 'unset VAR' et non 'unset $VAR'
//if unset + rien -> affiche/ne fait rien

/*
**if (!ft_strncmp(exec->tab[0], "unset", 6))
**	msh_unset()
*/

void	msh_unset(char **env, t_exec *exec)
{
	int	i;
	int	len;

	i = 1;
	if (!env || exec->tab[i])
		return ;				//!Error need a change
	if (exec->tab[i])
		len = ft_strlen(exec->tab[i]);
	
}