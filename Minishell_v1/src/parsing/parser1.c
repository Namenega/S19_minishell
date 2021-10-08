/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:03:32 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/07 17:36:36 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser(t_msh *msh)
{
	t_ast		*ast;
	t_parser	vars;

	if (!msh->tok)
		return ;
	vars = (t_parser){msh, msh->tok, msh->tok, NULL};
	ast = parser_pipe(&vars);
	if (!ast || vars.node)
		parser_error(&vars, ERR_SYNTAX, vars.node->lex);
	msh->ast = ast;
	msh->tok = free_tok(msh->tok);
}

t_ast	*parser_new(t_parser *vars, int type, t_tok *node)
{
	t_ast	*new;

	new = malloc(sizeof(*new));
	if (!new)
		parser_error(vars, ERR_MALLOC, NULL);
	new->type = type;
	if (node)
	{
		new->lex = ft_strdup(node->lex);
		if (!new->lex)
		{
			free(new);
			parser_error(vars, ERR_MALLOC, NULL);
		}
		vars->node = vars->node->next;
	}
	else
		new->lex = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
