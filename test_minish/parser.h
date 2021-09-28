/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:02:27 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/28 12:06:20 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "msh.h"

enum	e_cst
{
	CST_PIPE_SEQ,
	CST_CMD_LIST,
	CST_IO_REDIR,
	CST_IO_NBR,
	CST_IO_FILE,
	CST_IO_HERE,
	CST_WORD
};

typedef struct	s_cst t_cst;

struct s_cst
{
	int		type;
	char	*lexeme;
	t_cst	*left;
	t_cst	*right;
};

typedef struct s_parser
{
	t_lsttok	*first;
	t_lsttok	*node;
	t_cst		*tmp;
}			t_parser;

t_cst*	msh_parser(t_lsttok *tokens);
void	cst_print_tree(t_cst *tree);
void	error_parser(t_parser *vars);



void	search_words(t_cst *cmd, char **tab, size_t size, int nbr_left);
char	**get_word_in_tab(t_cst *cmd);
int		cst_add_words(t_cst *cmd, char **tab, size_t size, int nbr_left);
int		btree_level_count(t_cst *root);

#endif
