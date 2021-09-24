/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:02:36 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/24 15:57:32 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*utils_env_get_ifs(char **env)
{
	char	*ifs;

	ifs = utils_env_get_param(env, "IFS", 3);
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

char	*utils_env_get_param(char **env, char *var, int len)
{
	if (!env || !var)
		return (NULL);
	while (*env)
	{
		if (!ft_strncmp(*env, var, len) && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}