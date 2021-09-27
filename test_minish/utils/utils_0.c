/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:36:01 by namenega          #+#    #+#             */
/*   Updated: 2021/09/27 17:09:37 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	isnt_special(char c)
{
	if (c == '|' || c == '&' || c == '>' || c == '<' || c == '\"' || c == '\'')
		return (0);
	else
		return (1);
}

void	free_token_list(t_token *tok)
{
	t_lsttok	*tmp;

	tmp = tok->lsttok;
	while (tok->lsttok)
	{
		tmp = tok->lsttok;
		tok->lsttok = tok->lsttok->next;
		free(tmp);
	}
}

int		ft_intcmp(int a, int b)
{
	// int i;
	// int	j;
	// i = (int)a;
	// j = (int)b;
	if (!a || !b)
		return(0);
	if (a == b)
		return (1);
	return (0);
}

//!Uncomment this if '$' needed
/*void	is_dollar(char *line, t_token *tok)
{
	char	*s;
	int		i;

	i = 0;
	if (line[tok->i] && line[tok->i] == '$')
	{
		tok->i++;
		while (line[tok->i + i] && line[tok->i + i] != ' ')
			i++;
		s = malloc(sizeof(char) * i + 1);
		if (!s)
			return ;
		i = 0;
		while (line[tok->i + i] && line[tok->i + i] != ' ')
		{
			s[i] = line[tok->i + i];
			i++;
		}
		s[i] = '\0';
		while (line[tok->i] && line[tok->i] != ' ')
			tok->i++;
		tok->tokno++;
		lst_new_addback(s, DOLLAR, tok);
	}
}*/
