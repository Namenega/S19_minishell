/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:41:18 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 12:18:09 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(t_exec *exec)
{
	char	**env;

	env = exec->msh->env;
	if (exec->argv[1])
	{
		write(2, "env: illegal option or argument\n", 32);
		return (EXIT_FAILURE);
	}
	while (*env)
	{
		write(1, *env, ft_strlen(*env));
		write(1, "\n", 1);
		env++;
	}
	return (EXIT_SUCCESS);
}
