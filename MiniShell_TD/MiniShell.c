/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniShell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:05:03 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 11:10:30 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\033[32m Handling CTRL-C\033[0m\n");
	rl_on_new_line();			// Regenerate the prompt on a newline
	// if (*rl_line_buffer)			// Buffer empty
		// TODO:set RET to 130
	rl_replace_line("", 0);		// Clear the previous text
	rl_redisplay();				// Discplay the new buffer

}

void	msh_free(t_msh *msh)
{
	(void)msh;
}

void	msh_error(t_msh *msh, char *msg)
{
	(void)msh;
	printf("\033[31mEXIT_FAILURE\033[0m\n");
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

/*
**	TODO List
** - check free : line, tok, ast, exec
**
*/

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_msh	msh;
	t_exec	*exec;

	msh.env = utils_env_copy(env, utils_env_size(env) + 5);
	msh.path = NULL;
	msh.line = NULL;
	msh.tok = NULL;
	msh.ast = NULL;
	msh.ret[0] = '1';
	msh.ret[1] = '2';
	msh.ret[2] = '1';
	msh.ret[3] = '\0';
	msh.env_size = utils_env_size(env);
	msh.env_left = 5;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);		// Ignore SIGQUIT
	printf("Welcome! Exit by pressing CTRL-D.\n");
	set_path(&msh);
	msh.cwd = ft_strdup(utils_env_get_param(env, "PWD", 3));
	printf("\033[36mCWD\033[0m:%s\n", msh.cwd);
	while(1)
	{
		msh.line = readline("\033[32mmsh>\033[0m");
		if (*msh.line)					// ADD to history if not empty
		{
			// printf("\t\t\033[32mOK\033[0m\n"); // TODO: remove
			add_history(msh.line);
			lexer(&msh);
			// lexer_print(msh.tok);
			parser(&msh);
			// parser_print(msh.ast);
			we_word_expansion(&msh);
			// printf("\t \033[32mAFTER WORD EXPANSION:\033[0m\n");
			// parser_print(msh.ast);
			if (msh.ast->type == AST_PIPE)
				exec = cmd_get(&msh, msh.ast->left);
			else
				exec = cmd_get(&msh, msh.ast);
			// cmd_print(exec);
			which_cmd(&msh, exec);
			// exec->cmdpath = get_bin(&msh, exec->tab[0]);
			// if (!ft_strcmp(exec->tab[0], "unset"))
			// 	msh_unset(env, exec);
			// else
			// msh_cd(&msh, exec);
		}
	}
}

//cd /b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre/a/b/oinfre a/b/c/d/e/go2goinfre/a/b/c/d/e/go2goinfre
