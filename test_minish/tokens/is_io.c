/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:03:31 by namenega          #+#    #+#             */
/*   Updated: 2021/09/28 14:23:59 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

int	check_io(t_token *tok)
{
	int	i;

	i = tok->i;
	while (i < tok->i)
	{
		if (!ft_isdigit(tok->tmp[i]))
			return (0);
		tok->i++;
	}
	return (1);
}

void	is_io(t_token *tok)
{
	char	type;

	if (check_io(tok))
		new_tok(tok, IO_NUMBER);
	else
		new_tok(tok, WORD);
	if (tok->tmp[tok->pos] == '<')
		type = LESS;
	else
		type = GREAT;
	if (tok->tmp[tok->pos + 1] == tok->tmp[tok->pos])
	{
		type += 2;
		tok->pos++;
	}
	tok->pos++;
	new_tok(tok, type);
}
