/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:33:19 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/09 14:15:21 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	check_quotes(t_msh *msh)
{
	int	i;
	int	state;

	i = -1;
	state = WE_ST_FREE;
	while (msh->line[++i])
	{
		if (msh->line[i] == '\'' && state == WE_ST_FREE)
			state = WE_ST_SQUOTE;
		else if (msh->line[i] == '\'' && state == WE_ST_SQUOTE)
			state = WE_ST_FREE;
		else if (msh->line[i] == '\"' && state == WE_ST_FREE)
			state = WE_ST_DQUOTE;
		else if (msh->line[i] == '\"' && state == WE_ST_DQUOTE)
			state = WE_ST_FREE;
	}
	if (state == WE_ST_FREE)
		return (0);
	clean_msh(msh);
	return (print_error(MSG_MSH, ERR_QUOTES, NULL, EXIT_FAILURE));
}
