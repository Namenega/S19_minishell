/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:12:03 by namenega          #+#    #+#             */
/*   Updated: 2021/09/29 13:15:31 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"
#include "../includes/parser.h"

void	io_lst_new_addback(t_cst *cmd, t_getio *io)
{
	t_getio	*tmp;

	tmp = io_lst_new(cmd);
	if (!tmp)
		return ;
	io_lst_add_back(&io, tmp);
}

t_getio	*io_lst_new(t_cst *cmd)
{
	t_getio	*new;

	new = malloc(sizeof(t_getio));
	if (!new)
		return (NULL);						//! Erro msg need a change
	new->redir = cmd->lexeme;				//* >, >>, <, <<		> & >> : fd = 1		< & << : fd = 0
	if (cmd->left && cmd->left->type == CST_IO_NBR)
		new->fd = ft_atoi(cmd->left->lexeme);
	else
	{
		if (!ft_strcmp(new->redir, ">") || !ft_strcmp(new->redir, ">>"))
			new->fd = 1;
		else if (!ft_strcmp(new->redir, "<") || !ft_strcmp(new->redir, "<<"))
			new->fd = 0;
	}
	if (cmd->right && cmd->right->type == CST_WORD)
		new->filename = cmd->right->lexeme;
	//!oflag?
	new->next = NULL;
	return (new);
}

void	io_lst_add_back(t_getio **alst, t_getio *new)
{
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next)
		alst = &((*alst)->next);
	(*alst)->next = new;
}
