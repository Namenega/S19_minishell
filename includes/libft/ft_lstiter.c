/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:35:15 by namenega          #+#    #+#             */
/*   Updated: 2021/08/31 15:35:41 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TDERWEDU FCT
*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f)
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
}
