/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:12:03 by namenega          #+#    #+#             */
/*   Updated: 2021/09/29 15:24:59 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"
#include "parser.h"

void	get_io(t_launch *launch, t_cst *cmd)  //! Adapt to CST changes
{
	if (cmd->type == CST_IO_REDIR)
	{
		if (!launch->io)
		{
			launch->io = io_lst_new(cmd);
			launch->last = launch->io;
		}
		else
		{
			launch->last->next = io_lst_new(cmd);
			launch->last = launch->last->next;
		}
	}
	if (cmd->left)
		get_io(launch, cmd->left);
	if (cmd->right)
		get_io(launch, cmd->right);
}

static inline int	io_lst_oflag(char *type)
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

t_io	*io_lst_new(t_cst *cmd)
{
	t_io	*new;

	new = malloc(sizeof(t_io));
	if (!new)
		return (NULL);						//! Erro msg need a change
	if (cmd->left && cmd->left->type == CST_IO_NBR)
		new->fd = ft_atoi(cmd->left->lex);
	else
	{
		if (!ft_strcmp(cmd->lex, ">") || !ft_strcmp(cmd->lex, ">>"))
			new->fd = 1;
		else if (!ft_strcmp(cmd->lex, "<") || !ft_strcmp(cmd->lex, "<<"))
			new->fd = 0;
	}
	if (cmd->right && cmd->right->type == CST_WORD)
		new->filename = cmd->right->lex;
	new->oflag = io_lst_oflag(cmd->lex);
	new->next = NULL;
	return (new);
}

void	io_lst_print(t_io *lst)
{
	if (!lst)
		return ;
	printf("IO REDIR\n");
	printf("fd      : %i\n", lst->fd);
	printf("oflag   : %i\n", lst->oflag);
	printf("filename: %s\n", lst->filename);
	io_lst_print(lst->next);
}


// void	get_io_args(t_launch *launch, t_cst *cmd)
// {
// 	get_io(&launch->io, cmd);
// 	if (!launch->io->filename)
// 	{
// 		free(launch->io);
// 		launch->io = NULL;
// 	}
// }

// void	io_lst_new_addback(t_cst *cmd, t_io *io)
// {
// 	t_io	*tmp;

// 	tmp = io_lst_new(cmd);
// 	if (!tmp)
// 		return ;
// 	printf("TEST\n");
// 	io_lst_add_back(&io, tmp);
// }

// void	io_lst_add_back(t_io **alst, t_io *new)
// {
// 	if (!*alst)
// 	{
// 		*alst = new;
// 		return ;
// 	}
// 	while ((*alst)->next)
// 		alst = &((*alst)->next);
// 	(*alst)->next = new;
// }
