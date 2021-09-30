/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:57:07 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/30 10:43:34 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	cmd_word_count_sub(t_ast *ast, int *count)
{
	if (ast->type == AST_WORD)
		(*count)++;
	if (ast->left && ast->left->type != AST_IO_REDIR)
		cmd_word_count_sub(ast->left, count);
	if (ast->right && ast->right->type != AST_IO_REDIR)
		cmd_word_count_sub(ast->right, count);
}

int	cmd_word_count(t_ast *ast)
{
	int	count;

	count = 0;
	cmd_word_count_sub(ast, &count);
	return (count);
}

void	cmd_free(t_exec *exec)
{
	t_io	*io;
	t_io	*next;

	if (exec->cmdpath)
		free(exec->cmdpath);
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
	msh_error(cmd->msh, msg);
}

void	cmd_print(t_exec *exec)
{
	char	**tab;
	t_io	*io;

	if (!exec)
		return ;
	tab = exec->tab;
	io = exec->io;
	printf("\033[33m \t ### NEXT EXEC ###\033[0m\n");
	printf("\033[36m CMD \033[0m %s\n", exec->tab[0]);
	printf("\033[36m PATH\033[0m %s\n", exec->cmdpath);
	printf("\033[36m ARGS\033[0m\n");
	while (*tab)
		printf("\t%s\n", *tab++);
	while (io)
	{
		printf("\033[36m IO\033[0m\n");
		printf("\t\033[35m fd   \033[0m %i\n", io->fd);
		printf("\t\033[35m oflag\033[0m %i\n", io->oflag);
		printf("\t\033[35m file \033[0m %s\n", io->filename);
		io= io->next;
	}
	printf("\033[33m \t ### END ###\033[0m\n");
}