/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:31:35 by namenega          #+#    #+#             */
/*   Updated: 2021/09/27 14:31:11 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TDERWEDU FCT
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (lst)
	{
		while (*lst)
		{
			next = (*lst)->next;
			if (del)
				del((*lst)->content);
			free(*lst);
			*lst = next;
		}
	}
}
