/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:33:47 by namenega          #+#    #+#             */
/*   Updated: 2021/09/19 20:05:54 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//! echo + nothing = display a \n
//! echo + $wrong_thing = display a \n

void	ft_echo(t_token *tok)
{
	(void)tok;
	printf("echo test\n");
	tok->lsttok = tok->lsttok->next;
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