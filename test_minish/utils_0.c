/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:36:01 by namenega          #+#    #+#             */
/*   Updated: 2021/08/31 18:59:20 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	is_word(char c)
{
	if (c == '|' || c == '&' || c == '$' || c == '>' || c == '<' || c == '"' || c == ' ')
		return (0);
	else
		return (1);
}

void	is_pipe(char *line, t_token *tok)
{
	char		s[2];
	t_lsttok	*tmp;

	if (line[tok->i] && line[tok->i] == '|')
	{
		s[0] = line[tok->i];
		s[1] = '\0';
		printf("%c", line[tok->i]);
		tok->tokno++;
		tok->i++;
	}
	tmp = ft_lsttok_new(s, PIPE);
	if (!tmp)
		return ;
	ft_lsttok_add_back(&tok->lsttok, tmp);
	// printf("\ncontent = [%s]\n", tok->lsttok->content);
	// printf("type = [%d]\n", tok->lsttok->tok_type);
}

void	is_less(char *line, t_token *tok)
{
	int			i;
	char		*s;
	//t_lsttok	*tmp;

	i = 0;
	if (line[tok->i] && line[tok->i] == '<')
	{
		while (line[tok->i + i] && line[tok->i + i] == '<')
			i++;
		s = malloc(sizeof(char) * (i + 1));
		if (line[tok->i + 1] && line[tok->i + 1] == '<')
		{
			printf("%c", line[tok->i]);
			printf("%c", line[tok->i]);
			ft_strcpy(s, "<<");
			tok->tokno++;
			tok->i += 2;
		}
		else
		{
			printf("%c", line[tok->i]);
			ft_strcpy(s, "<");
			tok->tokno++;
			tok->i++;
		}
	}
}
