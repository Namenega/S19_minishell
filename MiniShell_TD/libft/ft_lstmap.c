/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:36:27 by namenega          #+#    #+#             */
/*   Updated: 2021/09/27 14:33:17 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TDERWEDU FCT
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *))
{
	t_list	*newlist;
	t_list	*start;

	if (!lst || !f)
		return (NULL);
	newlist = ft_lstnew(f(lst->content));
	if (!newlist)
		return (NULL);
	start = newlist;
	lst = lst->next;
	while (lst)
	{
		newlist->next = malloc(sizeof(t_list));
		if (!newlist->next)
		{
			ft_lstclear(&start, d);
			return (NULL);
		}
		newlist = newlist->next;
		newlist->content = f(lst->content);
		lst = lst->next;
	}
	newlist->next = NULL;
	return (start);
}
