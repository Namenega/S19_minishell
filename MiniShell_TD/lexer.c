/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:29:05 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/23 11:50:36 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_error_malloc(t_lexer *lex) //TODO: implement!!
{
	(void)lex;
	return ;
}

void	lexer_print_tokens(t_tok *token)
{
	char	*arr_type[] = {"PIPE", "GREAT", "LESS", "DGREAT",\
							 "DLESS", "WORD", "IO_NUMBER"};
	if (!token)
	{
		printf("\033[32m\tNo token to print!\033[0m \n");
		return;		
	}
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

void	lexer_new_token(t_lexer *lex, int type)
{
	t_tok	*new;
	char	*lexeme;

	if (lex->i_p == lex->i)
		return ;
	new = malloc(sizeof(*new));
	if (!new)
		lexer_error_malloc(lex);
	lexeme = ft_substr(lex->line, lex->i_p, lex->i - lex->i_p);
	lex->i_p = lex->i;
	if (!lexeme)
	{
		free(new);
		lexer_error_malloc(lex);
	}
	*new = (t_tok){lexeme, type, NULL};
	if (!lex->first)
	{
		lex->first = new;
		lex->last = new;
		return ;
	}
	lex->last->next = new;
	lex->last = new;
}

void	lexer_handle_blank(t_lexer *lex)
{
	lexer_new_token(lex, WORD);
	lex->i++;
	lex->i_p = lex->i;
}

void	lexer_handle_quote(t_lexer *lex)
{
	char	quote;

	quote = lex->line[lex->i];
	lex->i++;
	while (lex->line[lex->i] && lex->line[lex->i] != quote)
		lex->i++;
	if (lex->line[lex->i] != quote)
		exit(1);
	lex->i++;
}

int	lexer_check_io_nbr(t_lexer *lex)
{
	int	i_p;

	i_p = lex->i_p;
	while (i_p < lex->i_p)
	{
		if (lex->line[i_p] < '0' || lex->line[i_p] > '9')
			return 0;
		i_p++;
	}
	return 1;
}

void	lexer_handle_io(t_lexer *lex)
{
	char	type;

	if (lexer_check_io_nbr(lex))
		lexer_new_token(lex, IO_NUMBER);
	else
		lexer_new_token(lex, WORD);
	if (lex->line[lex->i] == CHR_LESS)
		type = LESS;
	else
		type = GREAT;
	if (lex->line[lex->i + 1] == lex->line[lex->i])
	{
		type += 2;
		lex->i++;
	}
	lex->i++;
	lexer_new_token(lex, type);
}

void	lexer_handle_pipe(t_lexer *lex)
{
	lexer_new_token(lex, WORD);
	lex->i++;
	lexer_new_token(lex, PIPE);
}

t_tok*	msh_lexer(char *line)
{
	t_lexer	lex;

	if (!line || !*line)
		return NULL;
	lex = (t_lexer){0, 0, NULL, NULL, line};
	while (line[lex.i])
	{
		if (line[lex.i] == CHR_BLANK)
			lexer_handle_blank(&lex);
		else if (line[lex.i] == CHR_DQUOTE || line[lex.i] == CHR_QOUTE)
			lexer_handle_quote(&lex);
		else if (line[lex.i] == CHR_LESS || line[lex.i] == CHR_GREAT)
			lexer_handle_io(&lex);
		else if (line[lex.i] == CHR_PIPE)
			lexer_handle_pipe(&lex);
		else
			lex.i++;
	}
	lexer_new_token(&lex, WORD);
	return lex.first;
}
