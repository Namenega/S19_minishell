/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:33:47 by namenega          #+#    #+#             */
/*   Updated: 2021/09/30 15:01:56 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/msh.h"

//! echo + -n + smtg = display without \n
//! echo + -n + nothing = display nothing
//! echo $ = $
//! echo $_ = un truc chelou
//! echo + $wrong_thing = display a \n
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
		return ;
	}
	else if (!tok->lsttok->next)
		write(1, "\n", 1);
}
