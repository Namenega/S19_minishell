/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:57:07 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/29 17:57:44 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"
#include "parser.h"

/* TODO: all ERR in ine header */
# define ERR_MALLOC		"Malloc error."

typedef struct s_io	t_io;

typedef struct s_io
{
	int			fd;
	int			oflag;
	char		*filename;
	t_io	*next;
}				t_io;

typedef struct s_exec
{
	char		*cmdpath;
	int			size;
	char		**tab;
	t_io		*io;
	char		**env;
}				t_exec;

typedef struct s_cmd
{
	t_msh		*msh;
	t_exec		*exec;
	t_io		*tail;
	int			i;
}				t_cmd;

static void	cmd_word_count_sub(t_ast *ast, int *count)
{
	if (ast->type == CST_WORD)
		(*count)++;
	if (ast->left && ast->left->type != CST_IO_REDIR)
		word_count_sub(ast->left, count);
	if (ast->right && ast->right->type != CST_IO_REDIR)
		word_count_sub(ast->right, count);
}

static int	cmd_word_count(t_ast *ast)
{
	int	count;

	count = 0;
	word_count_sub(ast, &count);
	return (count);
}

t_exec	*cmd_get(t_msh *msh, t_ast *ast)
{
	t_cmd	cmd;
	t_exec	*exec;

	exec = malloc(sizeof(*exec));
	if (!exec)
		return (NULL);
	exec->size = word_count(exec);
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
		cmd_traversal(&cmd, ast);
	return (exec);
}

void	cmd_add_word(t_cmd *cmd, t_ast *ast)
{
	cmd->exec->tab[cmd->i++] = ast->lex;
	ast->lex = NULL;
}

void	cmd_ast_traversal(t_cmd *cmd, t_ast *ast)
{
	if (ast->left && ast->left->type == CST_WORD)
		cmd_add_word(cmd, ast->left);
	else if (ast->left && ast->left->type == CST_IO_REDIR)
		get_add_io(cmd, ast->left);
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

void	cmd_add_word(t_cmd *cmd, t_ast *ast)
{
	t_io	*new;

	new = malloc(sizeof(*new));
	if (!new)
		cmd_error(cmd, ERR_MALLOC);
	if (ast->left && ast->left->type == CST_IO_NBR)
		new->fd = ft_atoi(ast->left->lex);
	else if (!ft_strcmp(ast->lex, ">") || !ft_strcmp(ast->lex, ">>"))
		new->fd = 1;
	else // if (!ft_strcmp(ast->lex, "<") || !ft_strcmp(ast->lex, "<<"))
		new->fd = 0;
	if (ast->right && ast->right->type == CST_WORD)
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

void	cmd_free(t_exec *exec)
{
	t_io	*io;
	t_io	*next;

	if (exec->cmdpath)
		free_tab(exec->cmdpath);
	if (exec->tab)
		utils_free_tab(exec->tab);
	if (exec->env)
		utils_free_tab(exec->env);
	io = exec->io;
	next = exec->io;
	while (io)
	{
		next = io->next;
		free(io);
		io = next;
	}
}

void	cmd_error(t_cmd *cmd, char *msg)
{
	cmd_free(cmd->exec);
	msh_error(cmd->exec, msg);
}

typedef struct s_exec
{
	char		*cmdpath;
	int			size;
	char		**tab;
	t_io		*io;
	char		**env;
}				t_exec;


void	cmd_print(t_exec *exec)
{
	if (!exec)
		return ;
	printf("### Exec ###\n");
	printf("fd      : %i\n", lst->fd);
	printf("oflag   : %i\n", lst->oflag);
	printf("filename: %s\n", lst->filename);
	printf("### END ###\n");
	io_lst_print(lst->next);
}