/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:48:28 by namenega          #+#    #+#             */
/*   Updated: 2021/10/09 13:19:08 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

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
		i = 1;
		while (s[i] && s[i] == 'n')
			i++;
		if (s[i] && s[i] != 'n')
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

static int	if_echo_wrong_n(char **tab, int i, int x, int j)
{
	while (tab[i] && x != j)
	{
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (tab[i] && tab[i + 1])
	{
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			write(1, " ", 1);
	}
	else if (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		write(1, "\n", 1);
		i++;
	}
	if (tab[i])
		i++;
	return (i);
}

int	if_echo_n(char **tab, int i)
{
	int		j;
	int		x;

	j = 0;
	while (tab[i] && !ft_strncmp(tab[i], "-n", 2))
	{
		x = j;
		j = parse_n(tab[i]);
		if (j == 0)
			break ;
		i++;
	}
	if (j == 1 && tab[i])
		i = echo_multiple_n(i, tab);
	else
		i = if_echo_wrong_n(tab, i, x, j);
	return (i);
}
