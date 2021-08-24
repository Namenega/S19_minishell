/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_recon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:51:59 by pyg               #+#    #+#             */
/*   Updated: 2021/08/24 12:46:13 by pyg              ###   ########.fr       */
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
	int		i;

	i = 0;
	init_t_tok(&tok);
	// printf("[%s]\n", line);//!printf
	line = ft_strtrim(line, " \t\r\f\v");
	// printf("[%s]\n", line);//!printf
	while (line && line[i])
	{
		while (line[i] && line[i] != '"')
		{
			if (line[i] && line[i] == ' ')
				tok.tokno++;
			i++;
		}
		if (line[i] && line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			i++;
			tok.tokno++;
		}
		printf("[%d]\n", tok.tokno);//!printf
		// if (line && line[i])
		// 	i++;
	}
}