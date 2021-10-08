/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:13:56 by namenega          #+#    #+#             */
/*   Updated: 2021/10/08 12:17:56 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

static int	echo_multiple_n(int i, char **tab)
{
	if (!tab[i])
		return (0);
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			write(1, " ", 1);
		i++;
	}
	return (i);
}

static int	parse_n(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if (i == 2)
		return (1);
	else if (s[2] && s[2] == 'n')
	{
		i = 2;
		while (s[i] && s[i] == 'n')
			i++;
		if (s[i + 1] && s[i + 1] != 'n')
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

static int	if_echo_n(char **tab, int i)
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
	if (j == 1)
		i = echo_multiple_n(i, tab);
	else
	{
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			write(1, " ", 1);
		i++;
	}
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
