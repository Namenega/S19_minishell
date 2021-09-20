/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:02:27 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/02 19:01:03 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

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
	t_tok	*first;
	t_tok	*node;
	t_cst	*tmp;
}			t_parser;

t_cst*	msh_parser(t_tok *tokens);
void	cst_print_tree(t_cst *tree);
void	error_parser(t_parser *vars);

#endif
