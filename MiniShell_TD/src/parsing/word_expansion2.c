/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:22:20 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/30 10:30:01 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	we_error(t_we *we, char *msg)
{
	if (we->buff)
	{
		ft_vec_free(we->buff);
		we->buff = NULL;
	}
	if (we->old)
	{
		free(we->old);
		we->old = NULL;
	}
	if (we->ifs)
	{
		free(we->ifs);
		we->ifs = NULL;
	}
	msh_error(we->msh, msg);
}

void	we_add_word(t_we *we, t_vec *buff)
{
	char	*lex;
	t_ast	*new;

	if (!*buff->str)
		return ;
	*buff->ptr = '\0';
	lex = ft_strdup(buff->str);
	if (!lex)
		we_error(we, ERR_MALLOC);
	if (we->curr->lex)
	{
		new = malloc(sizeof(*new));
		if (!new)
			we_error(we, ERR_MALLOC);
		new->type = AST_WORD;
		new->lex = lex;
		new->right = NULL;
		new->left = we->curr->left;
		we->curr->left = new;
		we->curr = new;
	}
	else
		we->curr->lex = lex;
	*buff->str = '\0';
	buff->ptr = buff->str;
}
