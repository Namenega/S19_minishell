/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:53:24 by pyg               #+#    #+#             */
/*   Updated: 2021/09/19 18:53:53 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

static char	*strcpy_quote(char *line, t_token *tok, char c, char *s)
{
	while (line[tok->pos] && line[tok->pos] != c)
		s[tok->i++] = line[tok->pos++];
	if (line[tok->pos] == c)
	{
		s[tok->i] = c;
		s[tok->i + 1] = '\0';
		tok->pos++;
	}
	else
		s[tok->i] = '\0';
	return (s);
}

void	is_quote(char *line, t_token *tok, char c)
{
	char	*s;

	tok->i = 0;
	if (line[tok->pos] && line[tok->pos] == c)
	{
		tok->pos++;
		while (line[tok->pos + tok->i] && line[tok->pos + tok->i] != c)
			tok->i++;
		if (line[tok->pos + tok->i] == c)
			s = malloc(sizeof(char) * (tok->i + 3));
		else
			s = malloc(sizeof(char) * (tok->i + 2));
		if (!s)
			return ;
		s[0] = c;
		tok->i = 1;
		strcpy_quote(line, tok, c, s);
		tok->tokno++;
		lst_new_addback(s, WORD, tok);
	}
}
