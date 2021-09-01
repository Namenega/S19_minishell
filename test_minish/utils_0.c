/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:36:01 by namenega          #+#    #+#             */
/*   Updated: 2021/09/01 17:03:52 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	isnt_special(char c)
{
	if (c == '|' || c == '&' || c == '$' || c == '>' || c == '<' || c == '"' || c == '\'')
		return (0);
	else
		return (1);
}

void	is_pipe(char *line, t_token *tok)
{
	char		*s;

	if (line[tok->i] && line[tok->i] == '|')
	{
		s = ft_strdup("|");
		tok->tokno++;
		tok->i++;
		lst_new_addback(s, PIPE, tok);
	}
}

void	is_less(char *line, t_token *tok)
{
	int			i;
	char		*s;

	i = 0;
	if (line[tok->i] && line[tok->i] == '<')
	{
		if (line[tok->i + 1] && line[tok->i + 1] == '<')
		{
			s = ft_strdup("<<");
			tok->tokno++;
			tok->i += 2;
			lst_new_addback(s, DLESS, tok);
		}
		else
		{
			s = ft_strdup("<");
			tok->tokno++;
			tok->i++;
			lst_new_addback(s, LESS, tok);
		}
	}
}

void	is_more(char *line, t_token *tok)
{
	int			i;
	char		*s;

	i = 0;
	if (line[tok->i] && line[tok->i] == '>')
	{
		if (line[tok->i + 1] && line[tok->i + 1] == '>')
		{
			s = ft_strdup(">>");
			tok->tokno++;
			tok->i += 2;
			lst_new_addback(s, DGREAT, tok);
		}
		else
		{
			s = ft_strdup(">");
			tok->tokno++;
			tok->i++;
			lst_new_addback(s, GREAT, tok);
		}
	}
}

// void	is_dollar(char *line, t_token *tok)
// {
// 	char	*s;
// 	int		i;

// 	i = 0;
// 	if (line[tok->i] && line[tok->i] == '$')
// 	{
// 		tok->i++; //!Comment this if '$' needed
// 		while (line[tok->i + i] && line[tok->i + i] != ' ')
// 			i++;
// 		s = malloc(sizeof(char) * i + 1);
// 		if (!s)
// 			return ;
// 		i = 0;
// 		while (line[tok->i + i] && line[tok->i + i] != ' ')
// 		{
// 			s[i] = line[tok->i + i];
// 			i++;
// 		}
// 		s[i] = '\0';
// 		while (line[tok->i] && line[tok->i] != ' ')
// 			tok->i++;
// 		tok->tokno++;
// 		lst_new_addback(s, DOLLAR, tok);
// 	}
// }

void	is_dquote(char *line, t_token *tok)
{
	char	*s;
	int		i;

	i = 0;
	if (line[tok->i] && line[tok->i] == '"')
	{
		tok->i++;
		while (line[tok->i + i] && line[tok->i + i] != '"')
			i++;
		s = malloc(sizeof(char) * (i + 3));
		if (!s)
			return ;
		i = 1;
		while (line[tok->i + i - 1] && line[tok->i + i - 1] != '"')
		{
			s[i] = line[tok->i + i - 1];
			i++;
		}
		s[0] = '"';
		s[i] = '"';
		s[i + 1] = '\0';
		while (line[tok->i] && line[tok->i] != '"')
			tok->i++;
		tok->tokno++;
		tok->i++;
		lst_new_addback(s, WORD, tok);
	}
}

void		is_squote(char *line, t_token *tok)
{
	char	*s;
	int		i;

	i = 0;
	if (line[tok->i] && line[tok->i] == '\'')
	{
		tok->i++;
		while (line[tok->i + i] && line[tok->i + i] != '\'')
			i++;
		s = malloc(sizeof(char) * (i + 1));
		if (!s)
			return ;
		i = 1;
		while (line[tok->i + i - 1] && line[tok->i + i - 1] != '\'')
		{
			s[i] = line[tok->i + i - 1];
			i++;
		}
		s[0] = '\'';
		s[i] = '\'';
		s[i + 1] = '\0';
		while (line[tok->i] && line[tok->i] != '\'')
			tok->i++;
		tok->tokno++;
		tok->i++; //!Comment if '\'' needed
		lst_new_addback(s, WORD, tok);
	}
}

void	is_word(char *line, t_token *tok)
{
	char	*s;
	int		i;

	i = 0;
	while (line[tok->i + i] && isnt_special(line[tok->i + i]) == 1 && line[tok->i + i] != ' ')
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return ;
	i = 0;
	while (line[tok->i + i] && isnt_special(line[tok->i + i]) == 1 && line[tok->i + i] != ' ')
	{
		s[i] = line[tok->i + i];
		i++;
	}
	s[i] = '\0';
	while (line[tok->i] && isnt_special(line[tok->i]) == 1 && line[tok->i] != ' ')
		tok->i++;
	tok->tokno++;
	lst_new_addback(s, WORD, tok);
}
