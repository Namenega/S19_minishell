/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:13:56 by namenega          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/09 12:53:24 by namenega         ###   ########.fr       */
=======
/*   Updated: 2021/10/09 12:10:22 by tderwedu         ###   ########.fr       */
>>>>>>> b994d50c41001aa1327e7e1fe5a7ab2602d6818c
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

static int	normal_echo(char **tab, int i)
{
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return (i);
}

int	msh_echo(t_exec *exec)
{
	char	**tab;
	int		i;

	i = 1;
	if (!exec->argv)
		return (EXIT_FAILURE);
	tab = exec->argv;
	if (!tab[i])
	{
		write(1, "\n", 1);
		return (EXIT_FAILURE);
	}
	while (tab[i])
	{
		if (i == 1 && tab[i] && !ft_strncmp(tab[i], "-n", 2))
			i = if_echo_n(tab, i);
		else if (tab[i])
			i = normal_echo(tab, i);
	}
	return (EXIT_SUCCESS);
}
