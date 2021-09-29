/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:41:21 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/29 17:51:36 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/param.h>
#include "minishell.h"
#include "utils.h"

int	msh_pwd(char **argv)
{

	utils_free_tab(argv);
	return(EXIT_SUCCESS);
}