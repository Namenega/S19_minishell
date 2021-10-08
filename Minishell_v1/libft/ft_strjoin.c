/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:46:46 by namenega          #+#    #+#             */
/*   Updated: 2021/06/07 17:54:41 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*s1 == '\0' || *s2 == '\0')
		return (0);
	tab = malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tab)
		return (NULL);
	while (((char *)s1)[i] != '\0')
	{
		tab[i] = ((char *)s1)[i];
		i++;
	}
	while (((char *)s2)[j] != '\0')
	{
		tab[i + j] = ((char *)s2)[j];
		j++;
	}
	tab[i + j] = '\0';
	return (tab);
}

/*
** concat 2 str ds new str avec malloc
*/
