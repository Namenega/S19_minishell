/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:32:42 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/29 09:46:30 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "utils.h"

static int	msh_exit_get_int(char *argv)
{
	char 	*ptr;

	ptr = argv;
	while (*ptr && (*ptr >= '0' && *ptr <= '9'))
		ptr++;
	if (*ptr)
	{
		write(2, "msh: exit: ", 11);
		write(2, argv, ft_strlen(argv));
		write(2, ": numeric argument required\n", 28);
		return (0xFF);
	}
	return (ft_atoi(argv) & 0xFF);
}

int	msh_exit(t_msh *msh, int argc, char **argv)
{
	int	ret;

	write(1, "exit\n", 5);
	ret = ret_str_2_int(msh);
	if (argc > 1)
		ret = msh_exit_get_int(argv[1]);
	if (argc > 2)
		write(2, "msh: exit: too many arguments\n", 30);
	if (msh->env)
		utils_env_free(msh->env);
	if (msh->line)
		free(msh->line);
	if (msh->head)
		lexer_free(msh->head);
	if (msh->root)
		parser_free(msh->root);
	utils_env_free(argv);
	exit(ret);
}