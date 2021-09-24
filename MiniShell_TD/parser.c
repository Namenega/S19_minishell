/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:03:32 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/23 11:56:10 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	error_parser(t_parser *vars) //TODO: implement!!
{
	(void)vars;
	return ;
}

void	cst_print_tree2(t_cst *tree, int tab)
{
	char	*type[] = {"CST_PIPE_SEQ", "CST_CMD_LIST", "CST_IO_REDIR",\
							"CST_IO_NBR", "CST_IO_FILE", "CST_IO_HERE",\
							"CST_WORD"};
	char	*spaces[] = {" ", "\t", "\t\t","\t\t\t", "\t\t\t\t", "\t\t\t\t\t",
						"\t\t\t\t\t\t", "\t\t\t\t\t\t\t", "\t\t\t\t\t\t\t\t",
						"\t\t\t\t\t\t\t\t\t"};
	if (!tree)
		return ;
	if (tab > 9)
		tab = 9;
	printf("%s\033[36m%s\033[0m ", spaces[tab], type[tree->type]);
	if (tree->lex)
		printf("\033[33m>\033[0m%s\033[33m<\033[0m", tree->lex);
	printf("\n");
	if (tree->left)
	{
		printf("%sLEFT BRANCH\n", spaces[tab]);
		cst_print_tree2(tree->left, tab + 1);
	}
	if (tree->right)
	{
		printf("%sRIGHT BRANCH\n", spaces[tab]);
		cst_print_tree2(tree->right, tab + 1);
	}
}

void	cst_print_tree(t_cst *tree)
{
	cst_print_tree2(tree, 0);
}

void	cst_print_node(t_cst *tree)
{
	char	*arr_type[] = {"CST_PIPE_SEQ", "CST_CMD_LIST", "CST_IO_REDIR",\
							"CST_IO_NBR", "CST_IO_FILE", "CST_IO_HERE",\
							"CST_WORD"};
	if (!tree)
		return ;
	printf("  type: %s\n", arr_type[tree->type]);
	printf("lexeme: \033[33m>\033[0m%s\033[33m<\033[0m\n", tree->lex);
}

void	cst_delete_tree(t_cst *tree)
{
	if (!tree)
		return ;
	// printf(" =====> \033[31m cst_delete_tree\033[0m\n"); // RM
	// cst_print_node(tree); // RM
	if (tree->lex)
		free(tree->lex);
	cst_delete_tree(tree->left);
	cst_delete_tree(tree->right);
	free(tree);
}

t_cst*	parse_new_node(t_parser *vars, int type, t_tok *node)
{
	t_cst	*new;

	// printf(" =====> \033[33m parse_new_node\033[0m\n"); // RM
	new = malloc(sizeof(*new));
	if (!new)
		error_parser(vars);
	new->type = type;
	if (node)
	{
		new->lex = ft_strdup(node->lex);
		vars->node = vars->node->next;
	}
	else
		new->lex = NULL;
	new->left = NULL;
	new->right = NULL;
	// cst_print_node(new); // RM
	return new;
}

t_cst*	parse_io_file(t_parser *vars)
{
	t_cst	*io_file;
	t_cst	*filename;

	// printf(" =====> \033[33m parse_io_file\033[0m\n"); // RM
	io_file = NULL;
	if (vars->tmp->type != CST_IO_REDIR)
		error_parser(vars);
	if (!vars->node)
		return NULL;
	if ((vars->node->type - GREAT) <= DGREAT)
	{
		io_file = parse_new_node(vars, CST_IO_FILE, vars->node);
		if (!vars->node || vars->node->type != WORD)
		{
			cst_delete_tree(io_file);
			return NULL;
		}
		vars->tmp->right = io_file;
		filename = parse_new_node(vars, CST_WORD, vars->node);
		io_file->left = filename;
	}
	return io_file;
}

t_cst*	parse_io_here(t_parser *vars)
{
	t_cst	*io_here;
	t_cst	*filename;

	// printf(" =====> \033[33m parse_io_here\033[0m\n"); // RM
	io_here = NULL;
	if (vars->tmp->type != CST_IO_REDIR)
		error_parser(vars);
	if (!vars->node)
		return NULL;
	if (vars->node->type == DLESS)
	{
		io_here = parse_new_node(vars, CST_IO_HERE, vars->node);
		if (!vars->node || vars->node->type != WORD)
		{
			cst_delete_tree(io_here);
			return NULL;
		}
		vars->tmp->right = io_here;
		filename = parse_new_node(vars, CST_WORD, vars->node);
		io_here->left = filename;
	}
	return io_here;
}

t_cst*	parse_io_redir(t_parser *vars)
{
	t_tok	*token;
	t_cst	*io_redir;

	// printf(" =====> \033[33m parse_io_redir : START \033[0m\n"); // RM
	token = vars->node;
	if (!vars->node)
		return NULL;
	io_redir = parse_new_node(vars, CST_IO_REDIR, NULL);
	io_redir->left = NULL;
	vars->tmp = io_redir;
	if (vars->node->type == IO_NUMBER)
		io_redir->left = parse_new_node(vars, CST_IO_NBR, vars->node);
	if (vars->node->type == GREAT || vars->node->type == LESS || vars->node->type == DGREAT)
		io_redir->right = parse_io_file(vars);
	else if (vars->node->type == DLESS)
		io_redir->right = parse_io_here(vars);
	vars->tmp = NULL;
	if (!io_redir->right)
	{
		cst_delete_tree(io_redir);
		vars->node = token;
		return NULL;
	}
	// printf(" =====> \033[33m parse_io_redir : END \033[0m\n"); // RM
	return io_redir;
}

t_cst*	parse_cmd_list(t_parser *vars)
{
	t_cst	*cmd_list;
	t_cst	*node;

	// printf(" =====> \033[33m parse_cmd_list : START\033[0m\n"); // RM
	cmd_list = NULL;
	if (!vars->node)
		return NULL;
	// lexer_print_one(vars->node);// RM
	if (vars->node->type == WORD)
		node = parse_new_node(vars, CST_WORD, vars->node);
	else
		node = parse_io_redir(vars);
	if (node)
	{
		// printf(" =====> \033[33m parse_cmd_list: MIDDLE\033[0m\n"); // RM
		cmd_list = parse_new_node(vars, CST_CMD_LIST, NULL);
		cmd_list->left = node;
		cmd_list->right = parse_cmd_list(vars);
	}
	// printf(" =====> \033[33m parse_cmd_list : END \033[0m\n"); // RM
	return cmd_list;
}

t_cst*	parse_pipe_seq(t_parser *vars)
{
	t_cst	*pipe_seq;
	t_cst	*cmd_list;

	cmd_list = parse_cmd_list(vars);
	if (!cmd_list || !vars->node)
		return cmd_list;
	// printf(" =====> \033[33m parse_pipe_seq : MIDDLE \033[0m\n"); // RM
	if (vars->node->type != PIPE)
	{
		cst_delete_tree(cmd_list);
		return NULL;
	}
	vars->tmp = cmd_list;
	pipe_seq = parse_new_node(vars, CST_PIPE_SEQ, vars->node);
	vars->tmp = NULL;
	pipe_seq->left = cmd_list;
	pipe_seq->right = parse_pipe_seq(vars);
	if (!pipe_seq->right)
	{
		cst_delete_tree(pipe_seq);
		return NULL;
	}
	return pipe_seq;
}

t_cst*	msh_parser(t_tok *tokens)
{
	t_cst		*cst;
	t_parser	vars;

	if (!tokens)
		return NULL;
	vars = (t_parser){tokens, tokens, NULL};
	cst = parse_pipe_seq(&vars);
	if (!cst || vars.node)
    {
		printf("Syntax Error near: %s\n", vars.node->lex);
		return NULL;
    }
	return cst;
}
