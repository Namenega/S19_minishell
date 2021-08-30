/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_recon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:51:59 by pyg               #+#    #+#             */
/*   Updated: 2021/08/30 19:15:58 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//token : A sequence of characters considered a single unit by the shell. It is either a word or an operator.
//! "salut ca va" est splitted

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
	// char	**tmp;
	int		i;
	// int		j;

	i = 0;
	init_t_tok(&tok);
	// printf("[%s]\n", line);//!printf
	line = ft_strtrim(line, " \t\r\f\v");
	// tmp = ft_split(line, ' ');
	// printf("[%s]\n", line);//!printf
	// while (line && line[i])
	// {
	// 	while (line[i] && line[i] != '"')
	// 	{
	// 		if (line[i] && line[i] == ' ')
	// 			tok.tokno++;
	// 		i++;
	// 	}
	// 	if (line[i] && line[i] == '"')
	// 	{
	// 		i++;
	// 		while (line[i] && line[i] != '"')
	// 			i++;
	// 		i++;
	// 		tok.tokno++;
	// 	}
	// 	// if (line && line[i])
	// 	// 	i++;
	// }



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
			tok.tokno++;
			i++;
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
		else if (line[i] && line[i] == '&')
		{
			printf("%c", line[i]);
			//esperluette()
			tok.tokno++;
			i++;
		}
		else //other shit
		{
			while (line[i] && is_word(line[i]) == 1)
			{
				printf("%c", line[i]);
				i++;
			}
			tok.tokno++;
		}
		printf("[%d]\n", tok.tokno);//!printf
		// if (line[i])
		// 	i++;
		// printf("%c", line[i]);
	}





	// while (tmp && tmp[i])
	// {
	// 	j = 0;
	// 	while (tmp && tmp[i] && tmp[i][j])
	// 	{
	// 		if (tmp[i][j] && tmp[i][j] == '|') //
	// 		{
	// 			tok.tokno++;
	// 		}
	// 		else if (tmp[i][j] && tmp[i][j] == '<')
	// 		{
	// 			if (tmp[i][j + 1] && tmp[i][j + 1] == '<')
	// 			{
	// 				tok.tokno++;
	// 				j++;
	// 			}
	// 			else
	// 				tok.tokno++;
	// 		}
	// 		else if (tmp[i][j] && tmp[i][j] == '>')
	// 		{
	// 			if (tmp[i][j + 1] && tmp[i][j + 1] == '>')
	// 			{
	// 				tok.tokno++;
	// 				j++;
	// 			}
	// 			else
	// 				tok.tokno++;
	// 		}
	// 		else if (tmp[i][j] && tmp[i][j] == '$')
	// 		{
	// 			//dollar()
	// 			tok.tokno++;
	// 		}
	// 		else if (tmp[i][j] && tmp[i][j] == '"') //dquote
	// 		{
	// 			j++;
	// 			while (tmp[i][j] && tmp[i][j] != '"')
	// 				j++;
	// 			tok.tokno++;
	// 		}
	// 		else if (tmp[i][j] && tmp[i][j] == '\'') //squote
	// 		{
	// 			j++;
	// 			while (tmp[i][j] && tmp[i][j] != '\'')
	// 				j++;
	// 			tok.tokno++;
	// 		}
	// 		else if (tmp[i][j] && tmp[i][j] == '&')
	// 		{
	// 			//esperluette()
	// 			tok.tokno++;
	// 		}
	// 		else //other shit
	// 		{
	// 			while (tmp[i][j] && is_word(tmp[i][j]) == 1)
	// 			{
	// 				j++;
	// 			}
	// 			tok.tokno++;
	// 		}
	// 		// if (tmp[i][j])
	// 		j++;
	// 	}
	// 	i++;
	// }
}