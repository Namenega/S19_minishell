/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:02:36 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 12:33:25 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO: Refactoring

char	*utils_env_get_ifs(char **env)
{
	char	*ifs;

	ifs = msh_getenv(env, "IFS", 3);
	if (!ifs)
		ifs = ft_strdup(" \t\n");
	if (!ifs)
		return (NULL);
	return (ifs);
}

char	*utils_env_check_name(char *str)
{
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = str;
	if ((*ptr >= 'A' && *str <= 'Z') || (*ptr >= 'a' && *ptr <= 'z')
		|| *ptr == '_')
		ptr++;
	else
		return (NULL);
	while (*ptr && ((*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= 'a' && *ptr <= 'z')
			|| (*ptr >= '0' && *ptr <= '9') || *ptr == '_'))
		ptr++;
	return (ptr);
}

char	**utils_env_param(char **env, char *var, int len)
{
	if (!env || !var || !len)
		return (NULL);
	while (*env)
	{
		if (!ft_strncmp(*env, var, len)
			&& ((*env)[len] == '=' || (*env)[len] == '\0'))
			return (env);
		env++;
	}
	return (NULL);
}

char	*utils_env_go_2_val(char *var)
{
	if (!var)
		return (NULL);
	while (*var && *var != '=')
		var++;
	return (var + (*var == '='));
}

char	**utils_env_next_addr(t_msh *msh)
{
	char	**addr;

	if (msh->env_left)
	{
		addr = msh->env + msh->env_size - msh->env_left--;
		addr[1] = NULL;
		return (addr);
	}
	msh->env_left = 5;
	msh->env_size += 5;
	msh->env = grow_tab(msh->env, msh->env_size);
	if (!msh->env)
		return (NULL);
	addr = msh->env + msh->env_size - msh->env_left--;
	addr[1] = NULL;
	return (addr);
}
