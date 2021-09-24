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

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char	*buff;
	t_tok	*tokens;
	t_cst	*root;
	t_msh	msh;

	// signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);		// Ignore SIGQUIT
	printf("Welcome! Exit by pressing CTRL-D.\n");
	while(1)
	{
		buff = readline(">");
		if (*buff)					// ADD to history if not empty
		{
			add_history(buff);
			tokens = msh_lexer(buff);
			if (!tokens)
				return (1);
			lexer_print_tokens(tokens);
			root = msh_parser(tokens);
			if (!root)
				return (1);
			cst_print_tree(root);
			msh = (t_msh){env, buff, tokens, root, "123"};
			we_word_expansion(&msh);
			printf("\t \033[32mAFTER WORD EXPANSION:\033[0m\n");
			cst_print_tree(root);
			free(buff);
		}
	}
}
