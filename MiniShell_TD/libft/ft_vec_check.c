/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:09:17 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/04 16:52:05 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_vec_check(t_vec *vec, char *str)
{
	int		len;
	int		size;
	char	*new;

	len = ft_strlen(str) + 1;
	if ((vec->end - vec->ptr) > len)
		return (0);
	size = vec->end - vec->str;
	while ((size - (vec->ptr - vec->str)) < len)
		size *= 2;
	new = malloc(sizeof(*new) * size);
	if (!new)
	{
		ft_vec_free(vec);
		return (1);
	}
	len = vec->ptr - vec->str + 1;
	ft_memcpy(new, vec->str, len);
	printf("NEW VWC: %s\n", vec->str);
	free(vec->str);
	vec->str = new;
	vec->ptr = new + len - 1;
	vec->end = new + size;
	return (0);
}
