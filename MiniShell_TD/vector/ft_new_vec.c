/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:36:41 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/23 15:50:34 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	*ft_new_vec(size_t size)
{
	t_vec	*vec;

	if (!(vec = malloc(sizeof(t_vec))))
		return (NULL);
	if (!(vec->str = malloc(size)))
	{
		free(vec);
		return (NULL);
	}
	*vec->str = '\0';
	vec->ptr = vec->str;
	vec->end = vec->str + size;
	return (vec);
}
