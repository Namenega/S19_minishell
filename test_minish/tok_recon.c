/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_recon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:51:59 by pyg               #+#    #+#             */
/*   Updated: 2021/08/31 15:15:28 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//token : A sequence of characters considered a single unit by the shell. It is either a word or an operator.

void	init_t_tok(t_token *tok)
{
	tok->tokno = 0;
	tok->tokens = NULL;
	tok->dless = NULL;
	tok->dgreat = NULL;
	tok->great = 0;
	tok->less = 0;
	// return (tok);
}

void	tok_recon(char *line)
{
	t_token	tok;
	int		i;

	i = 0;
	init_t_tok(&tok);
	line = ft_strtrim(line, " \t\r\f\v");
	while (line && line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] && line[i] == '|') //
		{
			printf("%c", line[i]);
			tok.tokno++;
			i++;
		}
		else if (line[i] && line[i] == '<')
		{
			if (line[i + 1] && line[i + 1] == '<')
			{
				printf("%c", line[i]);
				printf("%c", line[i]);
				tok.tokno++;
				i += 2;
			}
			else
			{
				printf("%c", line[i]);
				tok.tokno++;
				i++;
			}
		}
		else if (line[i] && line[i] == '>')
		{
			if (line[i + 1] && line[i + 1] == '>')
			{
				printf("%c", line[i]);
				printf("%c", line[i]);
				tok.tokno++;
				i += 2;
			}
			else
			{
				printf("%c", line[i]);
				tok.tokno++;
				i++;
			}
		}
		else if (line[i] && line[i] == '$')
		{
			//dollar()
			printf("%c", line[i]);
			i++;
			while (line[i] && line[i] != ' ')
			{
				printf("%c", line[i]);
				i++;
			}
			tok.tokno++;
		}
		else if (line[i] && line[i] == '"') //dquote
		{
			printf("%c", line[i]);
			i++;
			while (line[i] && line[i] != '"')
			{
				printf("%c", line[i]);
				i++;
			}
			tok.tokno++;
			printf("%c", line[i]);
			i++;
		}
		else if (line[i] && line[i] == '\'') //squote
		{
			printf("%c", line[i]);
			i++;
			while (line[i] && line[i] != '\'')
			{
				printf("%c", line[i]);
				i++;
			}
			printf("%c", line[i]);
			tok.tokno++;
			i++;
		}
		// else if (line[i] && line[i] == '&')
		// {
		// 	printf("%c", line[i]);
		// 	tok.tokno++;
		// 	i++;
		// }
		else //other shit
		{
			while (line[i] && /*(line[i] != '|' && line[i] != '&' && line[i] != '$'
				&& line[i] != '>' && line[i] != '<' && line[i] != '"'
				&& line[i] != ' ')*/is_word(line[i]) == 1)
			{
				printf("%c", line[i]);
				i++;
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