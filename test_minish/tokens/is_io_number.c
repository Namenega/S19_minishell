/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_io_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:03:31 by namenega          #+#    #+#             */
/*   Updated: 2021/09/20 17:17:25 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

static int	is_openmax_range(char *s)
{
	int	i;
	int	io_num;

	i = 0;
	io_num = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	io_num = ft_atoi(s);
	if (io_num >= 0 && io_num < OPEN_MAX)
		return (1);
	return (0);
}

void	is_io_number(t_token *tok)
{
	char		*s;
	int			t;
	t_lsttok	*tmp;

	t = 0;
	s = NULL;
	tmp = tok->lsttok;
	while (tmp)
	{
		s = (char*)tmp->content;
		if (tmp->next)
			t = tmp->next->tok_type;
		if (is_openmax_range(s) == 1)
		{
			if (tmp->next && (t == 11 || t == 12 || t == 13 || t == 14))
				tmp->tok_type = 16;
		}
		tmp = tmp->next;
	}
}