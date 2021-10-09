/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:57:07 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/09 12:23:33 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

void	prep_next_cmd(t_msh *msh, t_ast *ast, t_exec *exec)
{
	t_cmd	cmd;

	exec->argc = cmd_word_count(ast);
	exec->argv = malloc(sizeof(char **) * (exec->argc + 1));
	if (!exec->argv)
		return ;
	exec->argv[exec->argc] = NULL;
	exec->io = NULL;
	cmd.msh = msh;
	cmd.exec = exec;
	cmd.tail = NULL;
	cmd.i = 0;
	if (ast)
	{
		cmd_ast_traversal(msh, &cmd, ast);
		exec->fct = NULL;
		if (!*exec->argv)
			return ;
		exec->fct = is_builtin(exec->argv[0]);
		if (!exec->fct)
			exec->cmdpath = get_cmd_path(exec, exec->argv[0]);
	}
}

void	cmd_ast_traversal(t_msh *msh, t_cmd *cmd, t_ast *ast)
{
	if (ast->type == AST_WORD && ast->lex)
	{
		cmd->exec->argv[cmd->i++] = ast->lex;
		ast->lex = NULL;
	}
	else if (ast->type == AST_IO_REDIR)
		cmd_add_io(msh, cmd, ast);
	if (ast->left)
		cmd_ast_traversal(msh, cmd, ast->left);
	if (ast->right)
		cmd_ast_traversal(msh, cmd, ast->right);
}

static inline void	cmd_add_io_fd(t_msh *msh, t_ast *io_redir, t_io *new)
{
	t_hd	*tmp;

	if (io_redir->left && io_redir->left->type == AST_IO_NBR)
		new->fd = ft_atoi(io_redir->left->lex);
	else if (io_redir->lex[0] == '>')
		new->fd = 1;
	else
		new->fd = 0;
	if (io_redir->lex[0] == '<' && io_redir->lex[1] == '<')
	{
		tmp = msh->hd_lst;
		new->fd_h = tmp->fd_h;
		msh->hd_lst = tmp->next;
		free(tmp);
	}
	else
		new->fd_h = -1;
}

static inline void	cmd_add_io_flag(t_ast *io_redir, t_io *new)
{
	if (io_redir->lex[0] == '<' && io_redir->lex[1] == '\0')
		new->oflag = (O_RDONLY);
	else if (io_redir->lex[0] == '>' && io_redir->lex[1] == '\0')
		new->oflag = (O_WRONLY | O_CREAT | O_TRUNC);
	else if (io_redir->lex[0] == '>' && io_redir->lex[1] == '>')
		new->oflag = (O_WRONLY | O_CREAT | O_APPEND);
	else
		new->oflag = -1;
}

void	cmd_add_io(t_msh *msh, t_cmd *cmd, t_ast *io_redir)
{
	t_io	*new;

	new = malloc(sizeof(*new));
	if (!new)
		error_cmd(cmd, ERR_MALLOC);
	new->filename = io_redir->right->lex;
	io_redir->right->lex = NULL;
	cmd_add_io_fd(msh, io_redir, new);
	cmd_add_io_flag(io_redir, new);
	new->next = NULL;
	if (!cmd->tail)
		cmd->exec->io = new;
	else
		cmd->tail->next = new;
	cmd->tail = new;
}
