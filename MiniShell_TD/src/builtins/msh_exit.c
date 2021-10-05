/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:32:42 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 15:16:22 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "utils.h"

// TODO: one HEADER with all MSGs
// #define	MSG_EXIT			"msh: exit: "
// #define	MSG_EXIT_USE		": numeric argument required\n"
// #define	MSG_EXIT_ARGS		"too many arguments\n"

int	msh_exit(t_msh *msh, t_exec *exec)
{
	int		ret;
	char	*val;
	char	*ptr;

	write(1, "exit\n", 5);
	ret = ret_str_2_int(msh);
	if (exec->tab[1])
	{
		val = exec->tab[1];
		ptr = exec->tab[1];
		while (*ptr && (*ptr >= '0' && *ptr <= '9'))
			ptr++;
		if (*ptr)
			return (msh_print_error(MSG_EXIT, val, MSG_EXIT_USE, 0xFF));
		ret = (ft_atoi(val) & 0xFF);
	}
	if (exec->tab[2])
		return (msh_print_error(MSG_EXIT, MSG_EXIT_ARGS, NULL, 0xFF));
	msh_free(msh);
	exit(ret);
}
