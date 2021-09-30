/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 08:57:30 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/30 10:36:44 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parser_pipe(t_parser *vars)
{
	t_ast	*pipe_seq;
	t_ast	*cmd_list;

	cmd_list = parser_cmd_list(vars);
	if (!cmd_list || !vars->node)
		return (cmd_list);
	if (vars->node->type != PIPE)
	{
		parser_free(cmd_list);
		return (NULL);
	}
	vars->tmp = cmd_list;
	pipe_seq = parser_new(vars, AST_PIPE, vars->node);
	vars->tmp = NULL;
	pipe_seq->left = cmd_list;
	pipe_seq->right = parser_pipe(vars);
	if (!pipe_seq->right)
	{
		parser_free(pipe_seq);
		return (NULL);
	}
	return (pipe_seq);
}

t_ast	*parser_cmd_list(t_parser *vars)
{
	t_ast	*cmd_list;
	t_ast	*node;

	cmd_list = NULL;
	if (!vars->node)
		return (NULL);
	if (vars->node->type == WORD)
		node = parser_new(vars, AST_WORD, vars->node);
	else
		node = parser_io_redir(vars);
	if (node)
	{
		cmd_list = parser_new(vars, AST_CMD_LIST, NULL);
		cmd_list->left = node;
		cmd_list->right = parser_cmd_list(vars);
	}
	return (cmd_list);
}

t_ast	*parser_io_redir(t_parser *vars)
{
	t_tok	*node;
	t_ast	*io_redir;

	io_redir = NULL;
	node = vars->node;
	if (!vars->node)
		return (NULL);
	if (vars->node->type == IO_NUMBER)
		vars->tmp = parser_new(vars, AST_IO_NBR, vars->node);
	if (!vars->node)
	{
		parser_free(vars->tmp);
		vars->tmp = NULL;
		return (NULL);
	}
	if (vars->node->type >= GREAT && vars->node->type <= DGREAT)
		io_redir = parser_io_file(vars);
	else if (vars->node->type == DLESS)
		io_redir = parser_io_here(vars);
	else
		parser_free(vars->tmp);
	vars->tmp = NULL;
	if (!io_redir)
		vars->node = node;
	return (io_redir);
}

t_ast	*parser_io_file(t_parser *vars)
{
	t_ast	*filename;
	t_ast	*io_file;
	t_ast	*io_nbr;

	io_nbr = vars->tmp;
	io_file = parser_new(vars, AST_IO_REDIR, vars->node);
	io_file->left = io_nbr;
	vars->tmp = NULL;
	if (!vars->node || vars->node->type != WORD)
	{
		parser_free(io_file);
		return (NULL);
	}
	filename = parser_new(vars, AST_WORD, vars->node);
	io_file->right = filename;
	return (io_file);
}

t_ast	*parser_io_here(t_parser *vars)
{
	t_ast	*filename;
	t_ast	*io_here;
	t_ast	*io_nbr;

	io_nbr = vars->tmp;
	io_here = parser_new(vars, AST_IO_REDIR, vars->node);
	io_here->left = io_nbr;
	vars->tmp = NULL;
	if (!vars->node || vars->node->type != WORD)
	{
		parser_free(io_here);
		return (NULL);
	}
	filename = parser_new(vars, AST_WORD, vars->node);
	io_here->right = filename;
	return (io_here);
}
