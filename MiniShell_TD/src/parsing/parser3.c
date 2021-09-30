/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 08:54:35 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/30 10:29:15 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_free(t_ast *tree)
{
	t_ast	*left;
	t_ast	*right;

	if (!tree)
		return ;
	left = tree->left;
	right = tree->right;
	if (tree->lex)
		free(tree->lex);
	free(tree);
	if (left)
		parser_free(tree->left);
	if (right)
		parser_free(tree->right);
}

void	parser_error(t_parser *vars, char *msg, char *opt)
{
	if (vars->tmp)
		parser_free(vars->tmp);
	if (opt)
	{
		printf("Syntax Error near: %s\n", opt);
		lexer_free(vars->head);
		msh_error(vars->msh, NULL);
	}
	lexer_free(vars->head);
	msh_error(vars->msh, msg);
}

static void	parser_print_2(t_ast *tree, char **types, char **tabs, int tab)
{
	if (!tree)
		return ;
	if (tab > 9)
		tab = 9;
	printf("%s\033[36m%s\033[0m ", tabs[tab], types[tree->type]);
	if (tree->lex)
		printf("\033[33m>\033[0m%s\033[33m<\033[0m", tree->lex);
	printf("\n");
	if (tree->left)
	{
		printf("%sLEFT BRANCH\n", tabs[tab]);
		parser_print_2(tree->left, types, tabs, tab + 1);
	}
	if (tree->right)
	{
		printf("%sRIGHT BRANCH\n", tabs[tab]);
		parser_print_2(tree->right, types, tabs, tab + 1);
	}
}

void	parser_print(t_ast *tree)
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
	parser_print_2(tree, types, tabs, 0);
}
