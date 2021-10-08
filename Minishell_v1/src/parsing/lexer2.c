/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:28:27 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/07 17:38:11 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	lexer_handle_pipe(t_lexer *lex)
{
	lexer_new(lex, WORD);
	lex->i++;
	lexer_new(lex, PIPE);
}

void	lexer_new(t_lexer *lex, int type)
{
	t_tok	*new;
	char	*lexeme;

	if (lex->i_p == lex->i)
		return ;
	new = malloc(sizeof(*new));
	if (!new)
		lexer_error(lex, ERR_MALLOC);
	lexeme = ft_substr(lex->line, lex->i_p, lex->i - lex->i_p);
	lex->i_p = lex->i;
	if (!lexeme)
	{
		free(new);
		lexer_error(lex, ERR_MALLOC);
	}
	*new = (t_tok){lexeme, type, NULL};
	if (!lex->head)
	{
		lex->head = new;
		lex->tail = new;
		return ;
	}
	lex->tail->next = new;
	lex->tail = new;
}

t_tok	*free_tok(t_tok *node)
{
	t_tok	*next;

	while (node)
	{
		next = node->next;
		free(node->lex);
		free(node);
		node = next;
	}
	return (NULL);
}

void	lexer_error(t_lexer *lex, char *msg)
{
	free_tok(lex->head);
	msh_error(lex->msh, msg);
}

void	print_tok(t_tok *token)
{
	char	*arr_type[7];

	arr_type[0] = "PIPE";
	arr_type[1] = "GREAT";
	arr_type[2] = "LESS";
	arr_type[3] = "DGREAT";
	arr_type[4] = "DLESS";
	arr_type[5] = "WORD";
	arr_type[6] = "IO_NUMBER";
	printf("\e[33m\t### TOKEN LIST ### \e[0m \n");
	while (token)
	{
		printf(" /----------------------\\ \n");
		printf("   type : %s \n", arr_type[token->type - 10]);
		printf(" lexeme : \e[33m>\e[0m%s\e[33m<\e[0m \n", token->lex);
		printf(" \\----------------------/ \n");
		token = token->next;
	}
	printf("\e[33m\t### END ### \e[0m \n");
}
