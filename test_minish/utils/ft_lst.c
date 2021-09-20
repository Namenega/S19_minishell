/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:54:00 by namenega          #+#    #+#             */
/*   Updated: 2021/09/20 12:43:32 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	lst_new_addback(char *s, int type, t_token *tok)
{
	t_lsttok	*tmp;

	tmp = ft_lsttok_new(s, type);
	if (!tmp)
		return ;
	ft_lsttok_add_back(&tok->lsttok, tmp);
	// free(s);
}


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

void	ft_lsttok_clear(t_lsttok **lst, void (*del)(void *))
{
	t_lsttok *next;

	if (lst)
		while (*lst)
		{
			next = (*lst)->next;
			if (del)
				del((*lst)->content);
			free(*lst);
			*lst = next;
		}
}
