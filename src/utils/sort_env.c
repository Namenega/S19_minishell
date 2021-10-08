/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:26:49 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 12:28:02 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	utils_env_swap(char **ptr, char **pvt)
{
	char	*tmp;

	if (ptr + 1 == pvt)
	{
		tmp = *pvt;
		*pvt = *ptr;
		*ptr = tmp;
	}
	else
	{
		tmp = *(pvt - 1);
		*(pvt - 1) = *pvt;
		*pvt = *ptr;
		*ptr = tmp;
	}
}

static void	utils_env_quicksort(char **lo, char **hi)
{
	char	**ptr;
	char	**pvt;

	if (lo >= hi)
		return ;
	pvt = hi;
	ptr = pvt - 1;
	while (ptr >= lo)
	{
		if (ft_strcmp(*ptr, *pvt) > 0)
		{
			utils_env_swap(ptr, pvt);
			pvt--;
		}
		ptr--;
	}
	utils_env_quicksort(lo, pvt - 1);
	utils_env_quicksort(pvt + 1, hi);
}

void	sort_env(char **env)
{
	char	**lo;

	if (!env)
		return ;
	lo = env;
	while (*env)
		env++;
	env--;
	if (env > lo)
		utils_env_quicksort(lo, env);
}
