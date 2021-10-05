/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_canonpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:14:38 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 11:40:30 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** Return the canonical path from PATH:
** - Multiple '/'s are collapsed to a single '/'.
** - Leading './'s and trailing '/.'s are removed.
** - Trailing '/'s are removed.
** - Non-leading '../'s and trailing '..'s are handled by removing
**   portions of the path.
** Variables:
** - base points just past the root directory
** - p points at beginning of path element we're considering.
** - q points just past the last kept directory.
*/

static inline void	msh_canonpath_backtrack(char **p, char **q, char *base)
{
	(*p) += 2;
	if ((*q) > base)
	{
		while (--(*q) > base && (*q)[0] != '/')
			;
	}
}

static inline void	msh_canonpath_cpy(char **p, char **q, char *base)
{
	if ((*q) > base)
		*(*q)++ = '/';
	while ((*p)[0] && (*p)[0] != '/')
		*(*q)++ = *(*p)++;
}

/*
** Return the canonical path from PATH:
** - Multiple '/'s are collapsed to a single '/'.
** - Leading './'s and trailing '/.'s are removed.
** - Trailing '/'s are removed.
** - Non-leading '../'s and trailing '..'s are handled by removing
**   portions of the path.
*/

char	*msh_canonpath(char *path)
{
	char	*result;
	char	*base;
	char	*p;
	char	*q;

	result = ft_strdup(path);
	if (!result)
		return (NULL);
	base = result + (result[0] == '/') + (result[1] == '/');
	p = base;
	q = base;
	while (p[0])
	{
		if (p[0] == '/')
			p++;
		else if (p[0] == '.' && (p[1] == '/' || p[1] == '\0'))
			p++;
		else if (p[0] == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0'))
			msh_canonpath_backtrack(&p, &q, base);
		else
			msh_canonpath_cpy(&p, &q, base);
	}
	q[0] = '\0';
	printf("RESULT:%s\n", result);
	return (result);
}
