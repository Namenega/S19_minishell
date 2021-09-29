/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_in_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:13:12 by namenega          #+#    #+#             */
/*   Updated: 2021/09/29 15:20:36 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	cst_add_words(t_cst *cmd, t_launch *launch, int nbr_left)
{
	int	i;

	i = 0;
	launch->tab[launch->size - nbr_left] = cmd->lex;
	cmd->lex = NULL;
	if (!launch->tab)
		return (0);
	nbr_left--;
	return (nbr_left);
}

static void	search_words(t_cst *cmd, t_launch *launch, int nbr_left)
{
	if (cmd->left && cmd->left->type == CST_WORD)
		nbr_left = cst_add_words(cmd->left, launch, nbr_left);
	if (cmd->right)
		search_words(cmd->right, launch, nbr_left);
}

static void	word_count_sub(t_cst *cmd, int *count)
{
	if (cmd->type == CST_WORD)
		(*count)++;
	if (cmd->left && cmd->left->type != CST_IO_REDIR)
		word_count_sub(cmd->left, count);
	if (cmd->right && cmd->right->type != CST_IO_REDIR)
		word_count_sub(cmd->right, count);
}

static int	word_count(t_cst *cmd)
{
	int	count;

	count = 0;
	word_count_sub(cmd, &count);
	return (count);
}

t_launch	*get_word_in_tab(t_cst *cmd)
{
	t_launch	*launch;
	int			nbr_left;
	int			i;

	i = 0;
	launch = malloc(sizeof(t_launch));
	if (!launch)
		return (NULL);
	launch->size = word_count(cmd);
	launch->io = NULL;
	launch->last = NULL;
	nbr_left = launch->size;
	launch->tab = malloc(sizeof(char *) * (launch->size + 1));
	if (!launch->tab)
		return (NULL);
	launch->tab[launch->size] = NULL;
	search_words(cmd, launch, nbr_left);
	return (launch);
}
