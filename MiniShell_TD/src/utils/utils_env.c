/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:02:36 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 15:13:27 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO: Refactoring

void	utils_env_swap(char **ptr, char **pvt)
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

void	utils_env_quicksort(char **lo, char **hi)
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

void	utils_env_sort(char **env)
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

void	utils_free_tab(char **env)
{
	if (!env)
		return ;
	while (*env)
	{
		free(*env);
		env++;
	}
	free(env);
}

size_t	utils_env_size(char **env)
{
	size_t	size;

	size = 0;
	if (!env)
		return (size);
	while (*env)
	{
		size++;
		env++;
	}
	return (size);
}

void	utils_env_print(char **tab)
{
	printf("### Start Of Tab ###\n");
	while (*tab)
		printf("\t%s\n", *tab++);
	printf("### End Of Tab ###\n");
}

char	**utils_env_copy(char **env, size_t size)
{
	char	**new_env;
	char	**entry;

	if (!env)
		return (NULL);
	new_env = malloc(sizeof(*new_env) * (size + 1));
	entry = new_env;
	if (!new_env)
		return (NULL);
	while (*env)
	{
		*entry = ft_strdup(*env);
		if (!entry)
		{
			free(new_env);
			return (NULL);
		}
		env++;
		entry++;
	}
	*entry = NULL;
	return (new_env);
}

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
	if (!env || !var || !len)
		return (NULL);
	while (*env)
	{
		if (!ft_strncmp(*env, var, len) && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
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
	char **addr;

	if (msh->env_left)
	{
		addr = msh->env + msh->env_size  - msh->env_left--;
		addr[1] = NULL;
		return (addr);
	}
	msh->env_left = 5;
	msh->env_size += 5;
	msh->env  = utils_env_copy(msh->env, msh->env_size);
	if (!msh->env)
		return (NULL);
	addr = msh->env + msh->env_size  - msh->env_left--;
	addr[1] = NULL;
	return (addr);
}
