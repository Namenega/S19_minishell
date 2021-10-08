/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:46:24 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 15:48:06 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// TODO: bad identifier!!

static int	find_env(char *s, char **env, int len)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], s, len)
			&& (env[i][len] == '=' || env[i][len] == '\0'))
			break ;
		i++;
	}
	if (env[i])
	{
		free(env[i]);
		while (env[i + 1])
		{
			env[i] = env[i + 1];
			i++;
		}
		env[i] = NULL;
		return (1);
	}
	return (0);
}

int	msh_unset(t_exec *exec)
{
	int		i;
	int		len;
	char	*ptr;

	i = 1;
	len = 0;
	if (!exec->msh->env)
		return (EXIT_FAILURE);
	while (exec->argv[i])
	{
		ptr = utils_env_check_name(exec->argv[i]);
		if (!ptr || *ptr != '\0')
		{
			write(2, MSG_UNSET, ft_strlen(MSG_UNSET));
			write(2, exec->argv[i], ft_strlen(exec->argv[i]));
			write(2, ERR_IDENTIFIER, ft_strlen(ERR_IDENTIFIER));
		}
		else
		{
			len = ft_strlen(exec->argv[i]);
			if (find_env(exec->argv[i], exec->msh->env, len))
				exec->msh->env_left++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
