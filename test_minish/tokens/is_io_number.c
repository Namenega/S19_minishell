/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_io_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:03:31 by namenega          #+#    #+#             */
/*   Updated: 2021/09/20 15:33:43 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

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
		if (!ft_strncmp(s, "0", 2) || !ft_strncmp(s, "1", 2)
			|| !ft_strncmp(s, "2", 2))
		{
			if (tmp->next && (t == 11 || t == 12 || t == 13 || t == 14))
				tmp->tok_type = 16;
		}
		tmp = tmp->next;
	}
}