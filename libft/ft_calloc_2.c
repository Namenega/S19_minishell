/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 12:23:04 by pyg               #+#    #+#             */
/*   Updated: 2021/06/07 17:35:51 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_2(size_t nmemb)
{
	void	*tab;

	tab = malloc(nmemb);
	if (!tab)
		return (NULL);
	ft_bzero(tab, nmemb);
	return (tab);
}
