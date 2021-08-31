/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_recon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:51:59 by pyg               #+#    #+#             */
/*   Updated: 2021/08/31 18:36:34 by namenega         ###   ########.fr       */
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
		if (line[tok.i] && is_word(line[tok.i]) == 0)
		{
			while (line[tok.i] && line[tok.i] == ' ')
				tok.i++;
			is_pipe(line, &tok);
			//is_less(line, &tok)
			if (line[tok.i] && line[tok.i] == '<')
			{
				if (line[tok.i + 1] && line[tok.i + 1] == '<')
				{
					printf("%c", line[tok.i]);
					printf("%c", line[tok.i]);
					tok.tokno++;
					tok.i += 2;
				}
				else
				{
					printf("%c", line[tok.i]);
					tok.tokno++;
					tok.i++;
				}
			}
			if (line[tok.i] && line[tok.i] == '>')
			{
				if (line[tok.i + 1] && line[tok.i + 1] == '>')
				{
					printf("%c", line[tok.i]);
					printf("%c", line[tok.i]);
					tok.tokno++;
					tok.i += 2;
				}
				else
				{
					printf("%c", line[tok.i]);
					tok.tokno++;
					tok.i++;
				}
			}
			if (line[tok.i] && line[tok.i] == '$')
			{
				//dollar()
				printf("%c", line[tok.i]);
				tok.i++;
				while (line[tok.i] && line[tok.i] != ' ')
				{
					printf("%c", line[tok.i]);
					tok.i++;
				}
				tok.tokno++;
			}
			if (line[tok.i] && line[tok.i] == '"') //dquote
			{
				printf("%c", line[tok.i]);
				tok.i++;
				while (line[tok.i] && line[tok.i] != '"')
				{
					printf("%c", line[tok.i]);
					tok.i++;
				}
				tok.tokno++;
				printf("%c", line[tok.i]);
				tok.i++;
			}
			if (line[tok.i] && line[tok.i] == '\'') //squote
			{
				printf("%c", line[tok.i]);
				tok.i++;
				while (line[tok.i] && line[tok.i] != '\'')
				{
					printf("%c", line[tok.i]);
					tok.i++;
				}
				printf("%c", line[tok.i]);
				tok.tokno++;
				tok.i++;
			}
		}
		else //other shit
		{
			while (line[tok.i] && is_word(line[tok.i]) == 1)
			{
				printf("%c", line[tok.i]);
				tok.i++;
			}
			tok.tokno++;
		}
		printf("[%d]\n", tok.tokno);//!printf
	}
}

//liste chaine avec 2var
// 1 : contenu de l'input
// 2 : type de token (word, dgreat, etc)
//3 : ->next