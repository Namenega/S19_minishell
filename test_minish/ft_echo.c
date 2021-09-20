/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:33:47 by namenega          #+#    #+#             */
/*   Updated: 2021/09/20 11:55:33 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//! echo + nothing = display a \n
//! echo + $wrong_thing = display a \n

void	ft_echo(t_token *tok)
{
	(void)tok;
	ft_putstr_fd("echo test", 1);
	write(1, "\n", 1);
	// tok->lsttok = tok->lsttok->next;
	// if (tok->lsttok->next)
	// {
	// 	tok->lsttok = tok->lsttok->next;
	// 	while (tok->lsttok && tok->lsttok->tok_type == WORD)
	// 	{
	// 		ft_putstr_fd((char *)tok->lsttok->content, 1);
	// 		tok->lsttok = tok->lsttok->next;
	// 	}
	// }
}