/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:26:50 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 15:38:26 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	hd_lst_new(t_parser *vars, t_ast *io_here)
{
	t_hd	*new;

	if (!io_here)
		return ;
	new = malloc(sizeof(*new));
	if (!new)
		parser_error(vars, ERR_MALLOC, NULL);
	new->io_here = io_here;
	new->fd_h = -1;
	new->next = NULL;
	if (!vars->msh->hd_lst)
		vars->msh->hd_lst = new;
	else
		vars->last->next = new;
	vars->last = new;
}

t_hd 	*free_hd_lst(t_hd *node)
{
	t_hd	*next;

	if (!node->next)
	{
		while (node)
		{
			next = node->prev;
			if (node->fd_h >= 0)
				close(node->fd_h);
			free(node);
			node = next;
		}
	}
	return (NULL);
}

void	hf_lst_input(t_msh *msh)
{
	t_hd	*node;
	t_hd	*next;

	node = msh->hd_lst;
	while (node)
	{
		next = node->next;
		node->fd_h = heredoc(msh, node->io_here);
		if (node->fd_h < 0)
		{
			free_msh(msh);
			return ;
		}
		node = next;
	}
}