/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:33:47 by namenega          #+#    #+#             */
/*   Updated: 2021/09/20 14:46:59 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//! echo + nothing = display a \n
//! echo + $wrong_thing = display a \n

void	ft_echo(t_token *tok)
{
	char *s;

	s = (char*)tok->lsttok->content;
	if (tok->lsttok->next)
	{
		tok->lsttok = tok->lsttok->next;
		if (s && s[0] == '\"')
		{
			s++;
			while (s && *s && *s != '\"')
			{
				write(1, s, 1);
				s++;
			}
		}
		else if (s && s[0] == '\'')
		{
			s++;
			while (s && *s && *s != '\'')
			{
				write(1, s, 1);
				s++;
			}
		}
		else
		{
			while (tok->lsttok && tok->lsttok->tok_type == WORD)
			{
				// if (tok->lsttok->content[0] == '\"')
				// {

				// }
				ft_putstr_fd((char *)tok->lsttok->content, 1);
				write(1, " ", 1);
				tok->lsttok = tok->lsttok->next;
			}
		}
		write(1, "\n", 1);
	}
	else
	{
		write(1, "\n", 1);
		tok->lsttok = tok->lsttok->next;
	}
	
}