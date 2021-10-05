/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:41:21 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 11:32:15 by namenega         ###   ########.fr       */
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

int	msh_pwd(t_msh *msh, t_exec *exec)
{
	(void)msh;
	ft_putstr_fd(exec->msh->cwd, 1);
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
