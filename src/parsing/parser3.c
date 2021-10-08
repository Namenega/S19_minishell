/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 08:54:35 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 18:17:17 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*free_ast(t_ast *tree)
{
	t_ast	*left;
	t_ast	*right;

	if (!tree)
		return (NULL);
	left = tree->left;
	right = tree->right;
	if (tree->lex)
		free(tree->lex);
	free(tree);
	if (left)
		free_ast(left);
	if (right)
		free_ast(right);
	return (NULL);
}

void	parser_error(t_parser *vars, char *msg)
{
	print_error(MSG_MSH, msg, NULL, EXIT_FAILURE);
	free_ast(vars->tmp);
	free_msh(vars->msh);
	exit(258);
	exit(EXIT_FAILURE);
}

static void	print_ast_2(t_ast *tree, char **types, char **tabs, int tab)
{
	if (!tree)
		return ;
	if (tab > 9)
		tab = 9;
	printf("%s\e[36m%s\e[0m ", tabs[tab], types[tree->type]);
	if (tree->lex)
		printf("\e[33m>\e[0m%s\e[33m<\e[0m", tree->lex);
	printf("\n");
	if (tree->left)
	{
		printf("%sLEFT BRANCH\n", tabs[tab]);
		print_ast_2(tree->left, types, tabs, tab + 1);
	}
	if (tree->right)
	{
		printf("%sRIGHT BRANCH\n", tabs[tab]);
		print_ast_2(tree->right, types, tabs, tab + 1);
	}
}

void	print_ast(t_ast *tree)
{
	char	*types[5];
	char	*tabs[10];

	types[0] = "AST_PIPE";
	types[1] = "AST_CMD_LIST";
	types[2] = "AST_IO_REDIR";
	types[3] = "AST_IO_NBR";
	types[4] = "AST_WORD";
	tabs[0] = " ";
	tabs[1] = "\t";
	tabs[2] = "\t\t";
	tabs[3] = "\t\t\t";
	tabs[4] = "\t\t\t\t";
	tabs[5] = "\t\t\t\t\t";
	tabs[6] = "\t\t\t\t\t\t";
	tabs[7] = "\t\t\t\t\t\t\t";
	tabs[8] = "\t\t\t\t\t\t\t\t";
	tabs[9] = "\t\t\t\t\t\t\t\t\t";
	print_ast_2(tree, types, tabs, 0);
}
