/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_recon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:51:59 by pyg               #+#    #+#             */
/*   Updated: 2021/09/28 14:24:17 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

//token : A sequence of characters considered a single unit by the shell. It is either a word or an operator.

void	init_t_tok(t_token *tok, char *line)
{
	tok->tokno = 0;
	tok->i = 0;
	tok->pos = 0;
	tok->tmp = line;
	tok->lsttok = NULL;
}

void	is_space(t_token *tok)
{
	new_tok(tok, WORD);
	tok->pos++;
	tok->i = tok->pos;
}

void	new_tok(t_token *tok, int type)
{
	char	*s;

	if (tok->i == tok->pos)
		return ;
	s = ft_substr(tok->tmp, tok->i, tok->pos - tok->i);
	tok->i = tok->pos;
	if (!s)
		exit(0); //! another exit/error msg maybe
	lst_new_addback(s, type, tok);
}

t_lsttok	*tok_recon(char *line)
{
	t_token	tok;

	if (!line || !*line)
		return (NULL);
	init_t_tok(&tok, line);
	while (line[tok.pos])
	{
		if (line[tok.pos] == ' ')
			is_space(&tok);
		else if (line[tok.pos] == '\'' || line[tok.pos] == '\"')
			is_quote(&tok);
		else if (line[tok.pos] == '>' || line [tok.pos] == '<')
			is_io(&tok);
		else if (line[tok.pos] == '|')
			is_pipe(&tok);
		else
			tok.pos++;
	}
	new_tok(&tok, WORD);
	// while (tok.lsttok) //!print lst of tokens
	// {
	// 	printf("\ncontent = [%s]\n", tok.lsttok->content);
	// 	printf("type = [%d]\n", tok.lsttok->tok_type);
	// 	tok.lsttok = tok.lsttok->next;
	// }
	return (tok.lsttok);
}
