/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:03:32 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/27 14:17:30 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser(t_msh *msh)
{
	t_cst		*cst;
	t_parser	vars;

	if (!msh->head)
		return ;
	vars = (t_parser){msh, msh->head, msh->head, NULL};
	cst = parser_pipe_seq(&vars);
	if (!cst || vars.node)
		parser_error(&vars, ERR_SYNTAX, vars.node->lex);
	msh->root = cst;
}

t_cst	*parser_new_node(t_parser *vars, int type, t_tok *node)
{
	t_cst	*new;

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
