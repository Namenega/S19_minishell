/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_more_less.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:52:18 by pyg               #+#    #+#             */
/*   Updated: 2021/09/19 18:52:32 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	is_less(char *line, t_token *tok)
{
	char		*s;

	if (line[tok->pos] && line[tok->pos] == '<')
	{
		if (line[tok->pos + 2] && line[tok->pos + 2] == '<')
		{
			ft_putstr_fd("Error : too many '<'\n", 1);
			free_token_list(tok);
		}
		else if (line[tok->pos + 1] && line[tok->pos + 1] == '<')
		{
			s = ft_strdup("<<");
			tok->pos += 2;
			lst_new_addback(s, DLESS, tok);
		}
		else
		{
			s = ft_strdup("<");
			tok->pos++;
			lst_new_addback(s, LESS, tok);
		}
		tok->tokno++;
	}
}

void	is_more(char *line, t_token *tok)
{
	char		*s;

	if (line[tok->pos] && line[tok->pos] == '>')
	{
		if (line[tok->pos + 2] && line[tok->pos + 2] == '>')
		{
			ft_putstr_fd("Error : too many '>'\n", 1);
			free_token_list(tok);
		}
		else if (line[tok->pos + 1] && line[tok->pos + 1] == '>')
		{
			s = ft_strdup(">>");
			tok->pos += 2;
			lst_new_addback(s, DGREAT, tok);
		}
		else
		{
			s = ft_strdup(">");
			tok->pos++;
			lst_new_addback(s, GREAT, tok);
		}
		tok->tokno++;
	}
}
