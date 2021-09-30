/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:28:27 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/30 10:10:13 by tderwedu         ###   ########.fr       */
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

void	lexer_free(t_tok *head)
{
	t_tok	*next;

	next = head->next;
	free(head->lex);
	free(head);
	while (next)
	{
		head = next;
		next = head->next;
		free(head->lex);
		free(head);
	}
}

void	lexer_error(t_lexer *lex, char *msg)
{
	lexer_free(lex->head);
	msh_error(lex->msh, msg);
}

void	lexer_print(t_tok *token)
{
	char	*arr_type[7];

	arr_type[0] = "PIPE";
	arr_type[1] = "GREAT";
	arr_type[2] = "LESS";
	arr_type[3] = "DGREAT";
	arr_type[4] = "DLESS";
	arr_type[5] = "WORD";
	arr_type[6] = "IO_NUMBER";
	printf("\033[33m\t### TOKEN LIST ### \033[0m \n");
	while (token)
	{
		printf(" /----------------------\\ \n");
		printf("   type : %s \n", arr_type[token->type - 10]);
		printf(" lexeme : \033[33m>\033[0m%s\033[33m<\033[0m \n", token->lex);
		printf(" \\----------------------/ \n");
		token = token->next;
	}
	printf("\033[33m\t### END ### \033[0m \n");
}
