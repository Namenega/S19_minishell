/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:29:41 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 11:45:51 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//TODO: on single HEADER to rule them all
#define	MSH_EXPORT		"msh: export: `"
#define	MSG_IDENTIFIER	"': not a valid identifier\n"

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

int	msh_export_var(t_exec *exec, char *exp)
{
	char	*value;
	char	*param;

	value = utils_env_check_name(exp);
	if (*value != '=')
		return (msh_print_error(MSH_EXPORT, exp, MSG_IDENTIFIER, EXIT_FAILURE));
	param = utils_env_get_param(exec->env, exp, value - exp);
	if (param)
	{
		param = param - (value - exp + 1);
		free(param);
	}
	else
	{
		param = utils_env_next_addr(exec->msh);
		if (!param)
			exec_error(exec, ERR_MALLOC);
	}
	param = ft_strdup(exp);
	if (!param)
		exec_error(exec, ERR_MALLOC);
	return (EXIT_SUCCESS);
}

int	msh_export(t_exec *exec)
{
	int	i;

	if (!exec->tab[1])
		return (msh_export_print(exec));
	i = 1;
	while (exec->tab[i])
	{
		msh_export_var(exec, exec->tab[i]);
		i++;//utils_env_get_param
	}
	return (EXIT_SUCCESS);
}