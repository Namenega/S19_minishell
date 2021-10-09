/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:19:26 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/09 11:35:19 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

pid_t	g_sig;

void	clean_msh(t_msh *msh)
{
	if (msh->line)
		free(msh->line);
	msh->line = NULL;
	if (msh->tok)
		msh->tok = free_tok(msh->tok);
	if (msh->ast)
		msh->ast = free_ast(msh->ast);
	if (msh->hd_lst)
		msh->hd_lst = free_hd_lst(msh->hd_lst);
}

t_msh	*free_msh(t_msh *msh)
{
	if (msh->line)
		free(msh->line);
	msh->line = NULL;
	if (msh->cwd)
		free(msh->cwd);
	msh->cwd = NULL;
	if (msh->tok)
		msh->tok = free_tok(msh->tok);
	if (msh->ast)
		msh->ast = free_ast(msh->ast);
	if (msh->env)
		msh->env = free_tab(msh->env);
	if (msh->hd_lst)
		msh->hd_lst = free_hd_lst(msh->hd_lst);
	return (NULL);
}

static inline void	init_msh(t_msh *msh, char **env)
{
	g_sig = 0;
	msh->env_left = 5;
	msh->env_size = size_tab(env) + msh->env_left;
	msh->env = grow_tab(env, msh->env_size);
	msh->line = NULL;
	msh->tok = NULL;
	msh->hd_lst = NULL;
	msh->ast = NULL;
	msh->ret[0] = '0';
	msh->ret[1] = '\0';
	msh->cwd = ft_strdup(msh_getenv(env, "PWD", 3));
	signal_handling();
}

int	main(int argc, char **argv, char **env)
{
	t_msh	msh;

	(void)argv;
	if (argc > 1)
		return (print_error(ERR_ARGC, NULL, NULL, EXIT_FAILURE));
	init_msh(&msh, env);
	while (1)
	{
		msh.line = readline("msh>");
		if (!msh.line)
			break ;
		else if (*msh.line)
		{
			add_history(msh.line);
			lexer(&msh);
			parser(&msh);
			we_word_expansion(&msh);
			get_here_doc(&msh);
			launcher(&msh);
			g_sig = 0;
		}
		g_sig = 0;
		clean_msh(&msh);
	}
	free_msh(&msh);
}
