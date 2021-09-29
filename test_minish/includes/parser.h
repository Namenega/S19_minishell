/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:02:27 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/29 14:08:00 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "msh.h"

enum	e_cst
{
	CST_PIPE,
	CST_CMD_LIST,
	CST_IO_REDIR,
	CST_IO_NBR,
	CST_IO_FILE, //deleted
	CST_IO_HERE, //deleted
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

t_cst*		msh_parser(t_lsttok *tokens);
void		cst_print_tree(t_cst *tree);
void		error_parser(t_parser *vars);


t_launch	*get_word_in_tab(t_cst *cmd);

void		io_lst_new_addback(t_cst *cmd, t_io *io);
t_io		*io_lst_new(t_cst *cmd/*, t_io **last*/);
t_io		*io_lst_last(t_io *lst);
void		io_lst_add_back(t_io **alst, t_io *new);

#endif
