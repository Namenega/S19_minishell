/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:32:42 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 13:25:39 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "utils.h"

int	msh_exit(t_exec *exec)
{
	int		ret;
	char	*val;
	char	*ptr;

	write(1, "exit\n", 5);
	ret = ret_atoi(exec->msh);
	if (exec->argv[1])
	{
		val = exec->argv[1];
		ptr = exec->argv[1];
		while (*ptr && (*ptr >= '0' && *ptr <= '9'))
			ptr++;
		if (*ptr)
		{
			print_error(MSG_EXIT, val, ERR_EXIT_USE, 0xFF);
			exit(0xFF);
		}
		ret = (ft_atoi(val) & 0xFF);
	}
	if (exec->argv[1] && exec->argv[2])
		return (print_error(MSG_EXIT, ERR_EXIT_ARGS, NULL, 0xFF));
	free_msh(exec->msh);
	free_exec(exec);
	exit(ret);
}
