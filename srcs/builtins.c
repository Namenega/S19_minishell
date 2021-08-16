/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:08:42 by pyg               #+#    #+#             */
/*   Updated: 2021/08/16 17:31:04 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/minishell.h"

int	ms_cd(char **args);
int	ms_help(char **args);
int	ms_exit(char **args);

char	*builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int (*builtin_func[]) (char **) = {
  &ms_cd,
  &ms_help,
  &ms_exit
};

int ms_num_builtins()
{
  return (sizeof(builtin_str) / sizeof(char *));
}

int	ms_cd(char **args)
{
	if (args[1] == NULL)
		fprintf(stderr, "msh: expected argument to \"cd\"\n");
	else
		if (chdir(args[1]) != 0)
			perror("msh");
	return (1);
}

int ms_help(char **args)
{
	int	i;

	i = 0;
	(void)args;
	printf("Namenega & Tderwedu's LSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	while (i < ms_num_builtins())
	{
		printf("	%s\n", builtin_str[i]);
		i++;
	}
	printf("Use the man command for information on other programs.\n");
	return (1);
}

int	ms_exit(char **args)
{
	(void)args;
	return (0);
}

int	ms_execute(char **args)
{
	int	i;

	i = 0;
	if (args[0] == NULL)
		return (1);
	while (i < ms_num_builtins())
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
			return ((*builtin_func[i])(args));
		i++;
	}
	return (ms_launch(args));
}
