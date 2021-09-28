/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:44:49 by namenega          #+#    #+#             */
/*   Updated: 2021/09/28 11:30:13 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "parser.h"

int	cst_add_words(t_cst *cmd, char **tab, size_t size, int nbr_left)
{
	int	i;

	i = 0;
	tab[nbr_left - size] = cmd->lexeme;
	cmd->lexeme= NULL;
	if (!tab)
		return (0);
	ft_strcpy(tab[nbr_left - size], cmd->lexeme);
	size--;
	return (size);
}


// int	cst_add_words(t_cst *cmd, char **tab, size_t size, int nbr_left)
// {
// 	int	i;

// 	i = 0;
// 	tab[nbr_left - size] = malloc(sizeof(char) * ft_strlen(cmd->lexeme) + 1);
// 	if (!tab)
// 		return (0);
// 	ft_strcpy(tab[nbr_left - size], cmd->lexeme);
// 	size--;
// 	return (size);
// }


void	search_words(t_cst *cmd, char **tab, size_t size, int nbr_left)
{
	if (cmd->left && cmd->left->type == CST_CMD_LIST)
	{
		printf("\t\t\t OK OK OK OK\n");
		search_words(cmd->left, tab, size, nbr_left);
	}
	if (cmd->left && cmd->left->type == CST_WORD)
		size = cst_add_words(cmd->left, tab, size, nbr_left);
	if (cmd->right)
		search_words(cmd->right, tab, size, nbr_left);
}

char	**get_word_in_tab(t_cst *cmd)
{
	char	**tab;
	size_t	size;
	int		nbr_left;

	size = 5;
	nbr_left = 5;
	tab = malloc(sizeof(char *) * size);
	if (!tab)
		return (NULL);
	search_words(cmd, tab, size, nbr_left);

	printf("tab = [%s]\n", tab[0]);
	printf("tab = [%s]\n", tab[1]);
	return (tab);
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
		get_word_in_tab(cst->left);
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