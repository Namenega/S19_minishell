/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_recon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:51:59 by pyg               #+#    #+#             */
/*   Updated: 2021/09/01 17:06:52 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//token : A sequence of characters considered a single unit by the shell. It is either a word or an operator.

void	init_t_tok(t_token *tok)
{
	tok->tokno = 0;
	tok->i = 0;
	tok->tokens = NULL;
	tok->dless = NULL;
	tok->dgreat = NULL;
	tok->great = 0;
	tok->less = 0;
	// return (tok);
}

void	tok_recon(char *line)
{
	t_token		tok;
	int			i;

	i = 0;
	init_t_tok(&tok);
	line = ft_strtrim(line, " \t\r\f\v");
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
		printf("[%d]\n", tok.tokno); //* used to print the nb of tokens
	}
	while (tok.lsttok/* && tok.lsttok->next*/) //* used to print the list
	{
		printf("\ncontent = [%s]\n", tok.lsttok->content);
		printf("type = [%d]\n", tok.lsttok->tok_type);
		tok.lsttok = tok.lsttok->next;
	}
}

//liste chaine avec 2var
// 1 : contenu de l'input
// 2 : type de token (word, dgreat, etc)
//3 : ->next