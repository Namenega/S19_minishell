/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:44:49 by namenega          #+#    #+#             */
/*   Updated: 2021/08/17 15:38:27 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	cmd(char *line)
{
	echo(line);
}

char	**ms_splitline(char *line)
{
	char	*s;
	char	**split_line;

	s = ft_strtrim(line, " \t\r\f\v");
	split_line = ft_split(s, ' ');
	if (!split_line)
		return NULL;
	return (split_line);
}

void	ms_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		line = readline("our_shell> ");
		if (line && *line)
			add_history(line);
		args = ms_splitline(line);
		if (*args)
			cmd(line);
		// status = ms_execute(args);
		free(line);
		free(args);
		// status = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	if (ac == 1)
		ms_loop();
	else
		printf("Error: Run ./minishell without any other argument\n");
	return (0);
}