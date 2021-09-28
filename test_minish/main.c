/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:44:49 by namenega          #+#    #+#             */
/*   Updated: 2021/09/28 15:02:29 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/msh.h"
#include "includes/parser.h"


// typedef struct s_fd
// {
// 	int		fd[2];
// }				t_fd;



// void	cmd(t_token *tok)
// {
// 	while (tok->lsttok)
// 	{
// 		if (!ft_strncmp((char *)tok->lsttok->content, "echo", 5))
// 			ft_echo(tok);
// 		else
// 			tok->lsttok = tok->lsttok->next;
// 	}
// }

void	ms_loop(void)
{
	char		*line;
	int			status;
	t_token		tok;
	t_cst		*cst;
	t_launch	*launch;

	status = 1;
	while (status)
	{
		line = readline("splinter_shell> ");
		if (line && *line)
			add_history(line);
		if (line)
			tok.lsttok = tok_recon(line);
		// status = ms_execute(tokens);
		cst = msh_parser(tok.lsttok);
		if (!cst)						//!WRONG !!! Error : need to clean then exit
			return ;
		cst_print_tree(cst);
		if (cst->type == CST_PIPE_SEQ)
			launch = get_word_in_tab(cst->left);
		else
			launch = get_word_in_tab(cst);
		
		// cmd(tok);
		free(line);
		free_token_list(&tok);
		// system("leaks minishell");
		// exit(0);
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

//* print list fct
// printf("[%d]\n", tok.tokno); //! used to print the nb of tokens
// while (tok.lsttok/* && tok.lsttok->next*/)
// {
// 	printf("\ncontent = [%s]\n", tok.lsttok->content);
// 	printf("type = [%d]\n", tok.lsttok->tok_type);
// 	tok.lsttok = tok.lsttok->next;
// }