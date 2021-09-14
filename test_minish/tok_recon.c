/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_recon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:51:59 by pyg               #+#    #+#             */
/*   Updated: 2021/09/14 18:13:32 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//token : A sequence of characters considered a single unit by the shell. It is either a word or an operator.

void	init_t_tok(t_token *tok)
{
	tok->tokno = 0;
	tok->i = 0;
	tok->lsttok = NULL;
}

t_lsttok	*tok_recon(char *line)
{
	t_token		tok;
	int			i;
	char *tmp;

	i = 0;
	// init_t_tok(&tok);
	tok = (t_token){0, 0, NULL};
	if (line)
	{
		tmp = line;
		line = ft_strtrim(line, " \t\r\f\v");
		free(line);
	}
	while (line && line[tok.i])
	{
		while (line[tok.i] && line[tok.i] == ' ')
			tok.i++;
		if (line[tok.i] && isnt_special(line[tok.i]) == 0)
		{
			is_pipe(line, &tok);
			is_less(line, &tok);
			is_more(line, &tok);
			is_dquote(line, &tok);
			is_squote(line, &tok);
		}
		else
			is_word(line, &tok);
		// printf("[%d]\n", tok.tokno); //! used to print the nb of tokens
	}
	return (tok.lsttok);
}
