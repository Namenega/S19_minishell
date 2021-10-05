/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:57:07 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 16:11:23 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_exec	*cmd_get(t_msh *msh, t_ast *ast, t_exec *exec)
{
	t_cmd	cmd;

	exec->size = cmd_word_count(ast);
	exec->tab = malloc(sizeof(char *) * (exec->size + 1));
	if (!exec->tab)
		return (NULL);
	exec->tab[exec->size] = NULL;
	exec->env = msh->env;
	exec->io = NULL;
	exec->cmdpath = NULL;
	exec->msh = msh;
	cmd.msh = msh;
	cmd.exec = exec;
	cmd.tail = NULL;
	cmd.i = 0;
	if (ast)
		cmd_ast_traversal(msh, &cmd, ast);
	return (exec);
}

void	cmd_add_word(t_cmd *cmd, t_ast *ast)
{
	cmd->exec->tab[cmd->i++] = ast->lex;
	ast->lex = NULL;
}

void	cmd_ast_traversal(t_msh *msh, t_cmd *cmd, t_ast *ast)
{
	if (ast->type == AST_WORD)
		cmd_add_word(cmd, ast);
	else if (ast->type == AST_IO_REDIR)
		cmd_add_io(msh, cmd, ast);
	if (ast->left)
		cmd_ast_traversal(msh, cmd, ast->left);
	if (ast->right)
		cmd_ast_traversal(msh, cmd, ast->right);
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

void	cmd_add_io(t_msh *msh, t_cmd *cmd, t_ast *ast)
{
	t_io	*new;
	// int		err_d;

	new = malloc(sizeof(*new));
	if (!new)
		cmd_error(cmd, ERR_MALLOC);
	if (ast->left && ast->left->type == AST_IO_NBR)
		new->fd = ft_atoi(ast->left->lex);
	else if (!ft_strcmp(ast->lex, ">") || !ft_strcmp(ast->lex, ">>"))
		new->fd = 1;
	else // if (!ft_strcmp(ast->lex, "<") || !ft_strcmp(ast->lex, "<<"))
		new->fd = 0;
	if (!ft_strcmp(ast->lex, "<<"))				//!Ajout du else if
	{
		new->heredoc_fd = heredoc(msh, ast);
		// close(new->heredoc_fd);
	}
	else
		new->heredoc_fd = -1;
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
