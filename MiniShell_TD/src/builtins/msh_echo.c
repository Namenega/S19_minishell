/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:13:56 by namenega          #+#    #+#             */
/*   Updated: 2021/10/01 13:51:56 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static void	normal_echo(char **tab, int i, t_exec *exec)
{
	while (tab[i])
	{
		ft_putstr_fd(tab[i], exec->io->fd);
		write(exec->io->fd, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

static int	echo_multiple_n(t_exec *exec, int i, char **tab)
{
	if (!tab[i + 1])
		return (0);
	i++;
	while (tab[i])
	{
		ft_putstr(tab[i], exec->io->fd);
		write(exec->io->fd, " ", 1);
		i++;
	}
	return (i);
}

static int	parse_n(char *s)
{
	int i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if (i == 2)
		return (1);
	else if (s[2] && s[2] == 'n')								//* echo -nnnn
	{
		i = 2;
		while (s[i] && s[i] == 'n')
			i++;
		if (s[i + 1] && s[i + 1] != 'n')						//* echo -nnnnpl
			return (0);
		else
			return (1);
	}
	else
		return (0);
}


static int	if_echo_n(char **tab, int i, t_exec *exec)
{
	int		j;

	j = 0;
	while (tab[i] && !ft_strncmp(tab[i], "-n", 2))
	{
		j = parse_n(tab[i]);
		if (j == 0)
			break ;
		i++;
	}
	if (j == 1)													//* echo -n -n -n || echo -nnnn
		i += echo_multiple_n(exec, i, tab);
	else														//* echo -nfadsfas
	{															//!WRONG
		ft_putstr_fd(tab[i], exec->io->fd);
		write(exec->io->fd, " ", 1);
		i++;
	}
	return (i);
}

void	msh_echo(t_exec *exec)
{
	char	**tab;
	int		i;

	i = 1;
	if (!exec->tab)
		return ;												//* Error msg need a change
	tab = exec->tab;
	if (!tab[i])
	{
		write(1, "\n", 1);
		return ;
	}
	while (tab[i])
	{
		if (i == 1 && tab[i] && !ft_strncmp(tab[i], "-n", 2))	//* echo -n
			i += ft_echo_n(tab, i, exec);
		else if (tab[i])										//* echo
			normal_echo(tab, i, exec);
	}
}
