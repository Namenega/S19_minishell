/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:09:17 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/29 15:49:43 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_vec_check(t_vec *vec, char *str)
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
		ft_vec_free(vec);
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
