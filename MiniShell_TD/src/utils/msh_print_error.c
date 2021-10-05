/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_print_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:17:40 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 11:40:59 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	msh_print_error(char *s1, char *s2, char *s3, int ret)
{
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
	return (ret);
}
