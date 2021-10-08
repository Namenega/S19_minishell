/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:30:55 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 12:31:04 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*msh_getenv(char **env, char *var, int len)
{
	if (!env || !var || !len)
		return (NULL);
	while (*env)
	{
		if (!ft_strncmp(*env, var, len)
			&& ((*env)[len] == '=' || (*env)[len] == '\0'))
			return (*env + len + ((*env)[len] == '='));
		env++;
	}
	return (NULL);
}
