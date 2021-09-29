/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:44:13 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/28 11:39:09 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// void	msh_error(t_msh *msh, char *msg)
// {
// 	(void)msh;
// 	(void)msg;
// }

int	ret_str_2_int(t_msh *msh)
{
	int	val;

	val = (msh->ret[0] - '0') * 100 + (msh->ret[1] - '0') * 10;
	val += (msh->ret[2] - '0');
	return (val);
}

void	ret_int_2_str(t_msh *msh, int ret)
{
	msh->ret[0] = ret / 100 + '0';
	ret /= 100; 
	msh->ret[1] = ret / 10 + '0';
	ret /= 10;
	msh->ret[2] = ret / 100 + '0';
}