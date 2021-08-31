/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:33:47 by namenega          #+#    #+#             */
/*   Updated: 2021/08/30 19:44:00 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//! echo + nothing = display a \n
//! echo + $wrong_thing = display a \n



static int	parse_echo(int i, char *s)
{
	while (s && s[i])
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '"')
			{
				printf("%c", s[i]);
				i++;
			}
			if (s && s[i])
				i++;
		}
		while (s && s[i] && s[i] != '\"')
		{
			if (s && s[i] && s[i] == ' ')
			{
				while (s && s[i] && s[i] == ' ')
					i++;
				printf(" ");
				break ;
			}
			printf("%c", s[i]);
			i++;
		}
	}
	return (i);
}

void	echo(char *line)
{
	int	i;
	char *s;

	i = 4;
	s = ft_strtrim(line, " \t\r\f\v");
	if (s && !(ft_strncmp(s, "echo ", 5)))
	{
		// printf("|%s|\n", s);
		while (s && s[i] && s[i] == ' ')
			i++;
		parse_echo(i, s);
		printf("\n");
	}
}
