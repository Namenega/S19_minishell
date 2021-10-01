/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:57:07 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/01 16:29:26 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_exec	*cmd_get(t_msh *msh, t_ast *ast)
{
	t_cmd	cmd;
	t_exec	*exec;

	exec = malloc(sizeof(*exec));
	if (!exec)
		return (NULL);
	exec->size = cmd_word_count(ast);
	exec->tab = malloc(sizeof(char *) * (exec->size + 1));
	if (!exec->tab)
		return (NULL);
	exec->tab[exec->size] = NULL;
	exec->env = msh->env;
	exec->io = NULL;
	exec->cmdpath = NULL;
	cmd.msh = msh;
	cmd.exec = exec;
	cmd.tail = NULL;
	cmd.i = 0;
	if (ast)
		cmd_ast_traversal(&cmd, ast);
	return (exec);
}

void	cmd_add_word(t_cmd *cmd, t_ast *ast)
{
	cmd->exec->tab[cmd->i++] = ast->lex;
	ast->lex = NULL;
}

void	cmd_ast_traversal(t_cmd *cmd, t_ast *ast)
{
	if (ast->left && ast->left->type == AST_WORD)
		cmd_add_word(cmd, ast->left);
	else if (ast->left && ast->left->type == AST_IO_REDIR)
		cmd_add_io(cmd, ast->left);
	if (ast->right)
		cmd_ast_traversal(cmd, ast->right);
}

static inline int	cmd_io_oflag(char *type)
{
	if (type[0] == '<' && type[1] == '\0')
		return (O_RDONLY);
	else if (type[0] == '>' && type[1] == '\0')
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (type[0] == '>' && type[1] == '>')
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (0);
}

void	cmd_add_io(t_cmd *cmd, t_ast *ast)
{
	t_io	*new;

	new = malloc(sizeof(*new));
	if (!new)
		cmd_error(cmd, ERR_MALLOC);
	if (ast->left && ast->left->type == AST_IO_NBR)
		new->fd = ft_atoi(ast->left->lex);
	else if (!ft_strcmp(ast->lex, ">") || !ft_strcmp(ast->lex, ">>"))
		new->fd = 1;
	else if (!ft_strcmp(ast->lex, "<<"))				//!Ajout du else if
		heredoc(cmd->exec);
	else // if (!ft_strcmp(ast->lex, "<") || !ft_strcmp(ast->lex, "<<"))
		new->fd = 0;
	if (ast->right && ast->right->type == AST_WORD)
	{
		new->filename = ast->right->lex;
		ast->right->lex = NULL;
	}
	new->oflag = cmd_io_oflag(ast->lex);
	new->next = NULL;
	if (!cmd->tail)
		cmd->exec->io = new;
	else
		cmd->tail->next = new;
	cmd->tail = new;
}
