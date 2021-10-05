/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:44:13 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 14:02:02 by tderwedu         ###   ########.fr       */
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
	int		i;

	i = 1 + (ret >= 10) + (ret >= 100);
	msh->ret[i] = '\0';
	while (i--)
	{
		msh->ret[i] = (ret % 10 + '0');
		ret = ret / 10;
	}
}
