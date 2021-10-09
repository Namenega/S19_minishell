/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:24:21 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/09 12:10:22 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

static void	cmd_word_count_sub(t_ast *ast, int *count)
{
	if (ast->type == AST_IO_REDIR)
		return ;
	if (ast->type == AST_WORD && ast->lex)
		(*count)++;
	if (ast->left)
		cmd_word_count_sub(ast->left, count);
	if (ast->right)
		cmd_word_count_sub(ast->right, count);
}

int	cmd_word_count(t_ast *ast)
{
	int	count;

	count = 0;
	cmd_word_count_sub(ast, &count);
	return (count);
}
