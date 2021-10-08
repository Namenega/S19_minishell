/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:44:13 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 11:19:49 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ret_atoi(t_msh *msh)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	while (msh->ret[i])
		val = msh->ret[i++] - '0' + val * 10;
	return (val);
}

void	ret_itoa(t_msh *msh, int ret)
{
	int	i;

	i = 1 + (ret >= 10) + (ret >= 100);
	msh->ret[i] = '\0';
	while (i--)
	{
		msh->ret[i] = (ret % 10 + '0');
		ret = ret / 10;
	}
}
