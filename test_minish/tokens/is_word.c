/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:54:20 by pyg               #+#    #+#             */
/*   Updated: 2021/09/20 12:45:21 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	is_word(char *line, t_token *tok)
{
	char	*s;

	tok->i = 0;
	while (line[tok->pos + tok->i] && isnt_special(line[tok->pos + tok->i]) == 1
		&& line[tok->pos + tok->i] != ' ')
		tok->i++;
	s = malloc(sizeof(char) * (tok->i + 1));
	if (!s)
		return ;
	tok->i = 0;
	while (line[tok->pos + tok->i] && isnt_special(line[tok->pos + tok->i]) == 1
		&& line[tok->pos + tok->i] != ' ')
		s[tok->i++] = line[tok->pos + tok->i];
	s[tok->i] = '\0';
	tok->pos += tok->i;
	tok->tokno++;
	lst_new_addback(s, WORD, tok);
}
