/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:10:12 by pyg               #+#    #+#             */
/*   Updated: 2021/08/17 13:02:13 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/minishell.h"

char	**ms_splitline(char *line)
{
	int		buf_size;
	int		pos;
	char	**tokens;
	char	*tok;

	buf_size = MS_TOK_SIZE;
	pos = 0;
	tokens = malloc(sizeof(char *) * buf_size);
	if (!tokens)
		return (NULL);
	tok = strtok(line, MS_TOK_DELIM);
	while (tok != NULL)
	{
		tokens[pos] = tok;
		pos++;
		if (pos >= buf_size)
		{
			buf_size += MS_TOK_SIZE;
			tokens = realloc(tokens, buf_size * sizeof(char *));
			if (!tokens)
				return (NULL);
		}
		tok = strtok(NULL, MS_TOK_DELIM);
	}
	tokens[pos] = NULL;
	return (tokens);
}

char	*ms_readline(void)
{
	int		bufsize;
	int		pos;
	// char	*line;
	int		c;	
	char	*buffer;

	bufsize = MS_BUFFER; // = 1024
	pos = 0;
	buffer = malloc(sizeof(char *) * bufsize);
	if (!buffer)
		return (NULL);
	while (1)
	{
		c = getchar();
		if (c == EOF || c == '\n')
		{
			buffer[pos] = '\0';
			return (buffer);
		}
		else
			buffer[pos] = c;
		pos++;
		if (pos >= bufsize)
		{
			bufsize += MS_BUFFER;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
				return (NULL);
		}
	}
	// return (line);
}
