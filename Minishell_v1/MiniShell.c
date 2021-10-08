/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniShell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:05:03 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 15:04:49 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

/* Global for Signals */

pid_t	g_sig;

t_msh	*free_msh(t_msh *msh)
{
	if (msh->line)
		free(msh->line);
	msh->line = NULL;
	if (msh->cwd)
		free(msh->cwd);
	msh->cwd = NULL;
	if (msh->tok)
		msh->tok =  free_tok(msh->tok);
	if (msh->ast)
		msh->ast = free_ast(msh->ast);
	if (msh->env)
		msh->env = free_tab(msh->env);
	if (msh->hd_lst)
		msh->hd_lst = free_hd_lst(msh->hd_lst);
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	t_msh	msh;

	if (argc > 1)
	{
		write(2, ERR_ARGC, ft_strlen(ERR_ARGC));
		exit(EXIT_FAILURE);
	}
	g_sig = 0;
	msh.env_left = 5;
	msh.env_size = size_tab(env) + msh.env_left;
	msh.env = grow_tab(env, msh.env_size);
	msh.line = NULL;
	msh.tok = NULL;
	msh.hd_lst = NULL;
	msh.ast = NULL;
	msh.ret[0] = '0';
	msh.ret[1] = '\0';

	printf("Welcome! Exit by pressing CTRL-D.\n");
	msh.cwd = ft_strdup(msh_getenv(env, "PWD", 3));
	signal_handling();
	while(1)
	{
		msh.line = readline("\e[32mmsh>\e[0m");
		if (!msh.line)
			break;
		else if (*msh.line)
		{
			add_history(msh.line);
			lexer(&msh);
			parser(&msh);
			we_word_expansion(&msh);
			hf_lst_input(&msh);
			// handle_heredoc()&msh;
			launcher(&msh);
		}
	}
	printf("\e[31m \nBye Bye!\e[0m\n");
}
