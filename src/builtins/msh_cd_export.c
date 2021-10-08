/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:15:31 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 12:17:11 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	msh_cd_export(t_msh *msh, char *name, char *val)
{
	int		len_val;
	int		len_name;
	char	*var;
	char	**env;

	len_val = ft_strlen(val);
	len_name = ft_strlen(name);
	env = utils_env_param(msh->env, name, len_name);
	if (env)
	{
		var = malloc(sizeof(*var) * (len_name + len_val + 2));
		if (!var)
			return (EXIT_FAILURE);
		ft_memcpy(var, name, len_name);
		var[len_name] = '=';
		ft_memcpy(var + len_name + 1, val, len_val);
		var[len_name + 1 + len_val] = '\0';
		free(*env);
		*env = var;
	}
	return (EXIT_SUCCESS);
}
