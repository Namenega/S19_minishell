/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:54:00 by namenega          #+#    #+#             */
/*   Updated: 2021/08/31 18:05:13 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_lsttok	*ft_lsttok_new(void *content, int type)
{
	t_lsttok	*new;

	new = malloc(sizeof(t_lsttok));
	if (!new)
		return (NULL);
	new->content = content;
	new->tok_type = type;
	new->next = NULL;
	return (new);
}

void	ft_lsttok_add_back(t_lsttok **alst, t_lsttok *new)
{
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next)
	{
		alst = &((*alst)->next);
	}
	(*alst)->next = new;
}
