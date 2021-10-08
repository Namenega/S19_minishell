/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:36:41 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/29 15:49:51 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	*ft_vec_new(size_t size)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	if (!vec)
		return (NULL);
	vec->str = malloc(size);
	if (!vec->str)
	{
		free(vec);
		return (NULL);
	}
	*vec->str = '\0';
	vec->ptr = vec->str;
	vec->end = vec->str + size;
	return (vec);
}
