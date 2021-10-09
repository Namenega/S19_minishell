/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:57:07 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/09 12:10:22 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

t_io	*free_io(t_io *node)
{
	t_io	*next;

	if (!node)
		return (NULL);
	next = node;
	while (node)
	{
		next = node->next;
		free(node->filename);
		free(node);
		node = next;
	}
	return (NULL);
}

t_exec	*free_exec(t_exec *exec)
{
	if (!exec)
		return (NULL);
	if (exec->cmdpath)
		free(exec->cmdpath);
	exec->cmdpath = NULL;
	if (exec->argv)
		free_tab(exec->argv);
	exec->argv = NULL;
	free_io(exec->io);
	exec->io = NULL;
	return (NULL);
}

void	error_cmd(t_cmd *cmd, char *msg)
{
	print_error(MSG_MSH, msg, NULL, EXIT_FAILURE);
	free_exec(cmd->exec);
	free_msh(cmd->msh);
	exit(EXIT_FAILURE);
}

void	print_exec(t_exec *exec)
{
	char	**tab;
	t_io	*io;

	if (!exec)
		return ;
	tab = exec->argv;
	io = exec->io;
	printf("\e[33m \t ### NEXT EXEC ###\e[0m\n");
	printf("\e[36m CMD \e[0m %s\n", exec->argv[0]);
	printf("\e[36m PATH\e[0m %s\n", exec->cmdpath);
	printf("\e[36m ARGS\e[0m\n");
	while (*tab)
		printf("\t%s\n", *tab++);
	while (io)
	{
		printf("\e[36m IO\e[0m\n");
		printf("\t\e[35m fd   \e[0m %i\n", io->fd);
		if (io->fd_h >= 0)
			printf("\t\e[35m heredoc\e[0m %i\n", io->fd_h);
		printf("\t\e[35m oflag\e[0m %i\n", io->oflag);
		printf("\t\e[35m file \e[0m %s\n", io->filename);
		io = io->next;
	}
	printf("\e[33m \t ### END ###\e[0m\n");
}
