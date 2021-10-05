/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:29:41 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 10:31:37 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	msh_export_print(t_exec *exec)
{
	char	*value;
	char	**argv;

	argv = exec->env;
	while (*argv)
		argv++;
	argv = utils_env_copy(exec->env, argv - exec->env);
	utils_env_sort(argv);
	while (*argv)
	{
		value = utils_env_go_2_val(*argv);
		write(1, "declare -x ", 11);
		write(1, *argv, value - *argv - 1);
		write(1, "=\"", 2);
		write(1, value, ft_strlen(value));
		write(1, "\"\n", 2);
		argv++;
	}
	return (EXIT_SUCCESS);
}

int	msh_export(t_exec *exec)
{
	if (!exec->tab[1])
		return (msh_export_print(exec));
	return (EXIT_SUCCESS);
}