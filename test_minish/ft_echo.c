/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:33:47 by namenega          #+#    #+#             */
/*   Updated: 2021/09/23 13:52:51 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//! echo + nothing = display a \n
//! echo + $wrong_thing = display a \n
//! echo $ = $
//! echo $'t' = t
//! echo $"t" = t

void	skip_quote(char *s, int c, int d)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		if (s[0] == c)
		{
			if (s[i] == c)
				i++;
		}
		else if (s[0] == d)
		{
			if (s[i] == d)
				i++;
		}
		write(1, &s[i], 1);
		// if (s[i + 1])
		i++;
	}
}

void	ft_echo(t_token *tok)
{
	if (tok->lsttok->next && tok->lsttok->next->tok_type == WORD)
	{
		tok->lsttok = tok->lsttok->next;
		while (tok->lsttok && tok->lsttok->tok_type == WORD)
		{
			skip_quote((char *)tok->lsttok->content, '\"', '\'');
			if (tok->lsttok->next && tok->lsttok->next->tok_type == WORD)
				write(1, " ", 1);
			tok->lsttok = tok->lsttok->next;
		}
		write(1, "\n", 1);
	}
	else if (tok->lsttok->next && tok->lsttok->next->tok_type != WORD)
	{
		tok->lsttok = tok->lsttok->next;
	}
	else if (!tok->lsttok->next)
		write(1, "\n", 1);
}