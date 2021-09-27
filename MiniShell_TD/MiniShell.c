/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   test_readline.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tderwedu <tderwedu@student.s19.be>		 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/08/17 12:04:26 by tderwedu		  #+#	#+#			 */
/*   Updated: 2021/08/18 11:15:03 by tderwedu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <signal.h>
#include <sys/types.h>

#include "lexer.h"
#include "parser.h"
#include "word_expansion.h"
#include "utils.h"

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

void	msh_error(t_msh *msh, char *msg)
{
	(void)msh;
	(void)msg;
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char	*ret[4];
	t_msh	msh;

	msh = (t_msh){utils_env_copy(env, utils_env_size(env)), NULL, NULL, NULL,
	 		(char*)&ret};
	// signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);		// Ignore SIGQUIT
	printf("Welcome! Exit by pressing CTRL-D.\n");
	while(1)
	{
		msh.line = readline("msh>");
		if (*msh.line)					// ADD to history if not empty
		{
			add_history(msh.line);
			lexer(&msh);
			lexer_print(msh.head);
			parser(&msh);
			parser_print(msh.root);
			we_word_expansion(&msh);
			printf("\t \033[32mAFTER WORD EXPANSION:\033[0m\n");
			parser_print(msh.root);
			free(msh.line);
		}
	}
}
