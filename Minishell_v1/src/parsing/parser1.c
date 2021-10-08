/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:03:32 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 18:07:10 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser(t_msh *msh)
{
	t_ast		*ast;
	t_parser	vars;

	if (!msh->tok)
		return ;
	vars = (t_parser){msh, msh->tok, msh->tok, NULL, NULL};
	ast = parser_pipe(&vars);
	if (!ast || vars.node)
	{
		parser_syn_err(msh, vars.node);
		return ;
	}
	msh->ast = ast;
	msh->tok = free_tok(msh->tok);
}

void	parser_syn_err(t_msh *msh, t_tok *node)
{
	write(2, MSG_MSH, ft_strlen(MSG_MSH));
	write(2, ERR_SYNTAX, ft_strlen(ERR_SYNTAX));
	if (node)
		write(2, node->lex, ft_strlen(node->lex));
	else
		write(2, "`newline'", 9);
	write(2, "\n", 1);
	clean_msh(msh);
}

t_ast	*parser_new(t_parser *vars, int type, t_tok *node)
{
	t_ast	*new;

	new = malloc(sizeof(*new));
	if (!new)
		parser_error(vars, ERR_MALLOC);
	new->type = type;
	if (node)
	{
		new->lex = ft_strdup(node->lex);
		if (!new->lex)
		{
			free(new);
			parser_error(vars, ERR_MALLOC);
		}
		vars->node = vars->node->next;
	}
	else
		new->lex = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
