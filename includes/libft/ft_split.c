/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:27:35 by namenega          #+#    #+#             */
/*   Updated: 2021/06/07 18:02:28 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** compter le nbr de char sans c
*/

static int	ft_malloc_s(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (counter);
}

/*
** free
*/

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/*
** copier chaque chaine a l'endroit grace a substr
*/

static char	*ft_write_eachstr(const char *s, char c, char **tab)
{
	size_t	i;
	char	*dest;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dest = ft_substr(s, 0, i);
	if (dest == NULL)
		ft_free_split(tab);
	return (dest);
}

static char	**malloc_in_tab(char const *s1, char c)
{
	char	**tab;

	tab = malloc((ft_malloc_s(s1, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	return (tab);
}

/*
** malloc new str
** copie chaque char
*/

char	**ft_split(char const *s1, char c)
{
	int		i;
	int		j;
	int		counter;
	char	**tab;

	i = 0;
	j = 0;
	counter = 0;
	if (s1 == NULL)
		return (NULL);
	tab = malloc_in_tab(s1, c);
	while (s1[i])
	{
		while (s1[i] == c)
			i++;
		if (s1[i] && s1[i] != c)
		{
			tab[j++] = ft_write_eachstr(&s1[i], c, tab);
			while (s1[i] && s1[i] != c)
				i++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

/*
** tab de str separee par c
*/
