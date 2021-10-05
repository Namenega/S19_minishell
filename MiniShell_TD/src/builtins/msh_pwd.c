/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:41:21 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 08:50:14 by tderwedu         ###   ########.fr       */
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
	ft_putstr_fd(msh->cwd, 1);
	write(1, "\n", 1);
	return(EXIT_SUCCESS);
}
