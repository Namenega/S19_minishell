/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:09:17 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/27 14:26:38 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int	ft_check_vec(t_vec *vec, char *str)
{
	int		len;
	int		size;
	char	*new;

	len = ft_strlen(str);
	if ((vec->end - vec->ptr) < len)
		return (0);
	size = vec->end - vec->str;
	while ((size - (vec->ptr - vec->str)) < len)
		size *= 2;
	new = malloc(size);
	if (!new)
	{
		ft_free_vec(vec);
		return (1);
	}
	len = vec->ptr - vec->str;
	ft_memcpy(new, vec->str, len);
	free(vec->str);
	vec->str = new;
	vec->ptr = new + len;
	vec->end = new + len;
	return (0);
}
