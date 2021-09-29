/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:44:49 by namenega          #+#    #+#             */
/*   Updated: 2021/09/29 11:23:04 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/msh.h"
#include "includes/parser.h"


// typedef struct s_fd
// {
// 	int		fd[2];
// }				t_fd;


void	get_ionbr_ioredir(t_io *io, t_cst *cmd)  //! Adapt to CST changes
{
	if (cmd->type == CST_IO_NBR)
	{
		io->fd = ft_atoi(cmd->lexeme);
		printf("io_fd = [%d]\n", io->fd);
	}
	if (cmd->type == CST_IO_FILE)
	{
		io->redir = cmd->lexeme;
		printf("io_redir = [%s]\n", io->redir);
	}
	if (cmd->left)
		get_ionbr_ioredir(io, cmd->left);
	if (cmd->right)
		get_ionbr_ioredir(io, cmd->right);
}

void	get_io_args(t_launch *launch, t_cst *cmd)
{
	// printf("1.[%s]\n", cmd->lexeme);
	// printf("[%s]\n", cmd->lexeme);
	// printf("salut_2\n");
	// printf("salut_3\n");
	launch->io = malloc(sizeof(t_io));
	if (!launch->io)
		return ;								//! exit? free?
	launch->io->fd = 0;
	get_ionbr_ioredir(launch->io, cmd);
}

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
		cst_print_tree(cst);			//!print tree
		if (cst->type == CST_PIPE_SEQ)
			launch = get_word_in_tab(cst->left);
		else
			launch = get_word_in_tab(cst);
		if (cst->type == CST_PIPE_SEQ)
			get_io_args(launch, cst->left);
		else
			get_io_args(launch, cst);
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