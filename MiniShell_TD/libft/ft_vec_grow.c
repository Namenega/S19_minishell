/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_grow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:36:30 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/29 15:51:55 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	*ft_vec_grow(t_vec *vec)
{
	char	*new;
	size_t	len;
	size_t	size;

	size = (vec->end - vec->str);
	new = malloc(size * 2);
	if (!new)
	{
		ft_vec_free(vec);
		return (NULL);
	}
	len = vec->ptr - vec->str;
	ft_memcpy(new, vec->str, len);
	free(vec->str);
	vec->str = new;
	vec->ptr = new + len;
	vec->end = new + size * 2;
	return (vec);
}
