/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:02:27 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/30 10:48:20 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include "libft.h"
# include "minishell.h"
# include "utils.h"

/* TODO: all ERR in ine header */
# define ERR_MALLOC		"Malloc error."
# define ERR_QUOTES		"msh: error odd number of quotes."
# define ERR_SYNTAX		"Syntax Error near: %s\n"

# define TYPE_IO	0
# define TYPE_CMD	1

# define PIPE		10
# define GREAT		11
# define LESS		12
# define DGREAT		13
# define DLESS		14
# define WORD		15
# define IO_NUMBER	16

enum	e_symbols
{
	CHR_BLANK = ' ',
	CHR_LESS = '<',
	CHR_DQUOTE = '\"',
	CHR_QOUTE = '\'',
	CHR_GREAT = '>',
	CHR_PIPE = '|'
};

enum	e_ast
{
	AST_PIPE,
	AST_CMD_LIST,
	AST_IO_REDIR,
	AST_IO_NBR,
	AST_WORD
};

enum	e_state
{
	WE_ST_FREE,
	WE_ST_SQUOTE,
	WE_ST_DQUOTE
};

typedef struct s_tok	t_tok;
typedef struct s_ast	t_ast;
typedef struct s_msh	t_msh;

struct s_tok
{
	char	*lex;
	int		type;
	t_tok	*next;
};

struct s_ast
{
	int		type;
	char	*lex;
	t_ast	*left;
	t_ast	*right;
};

typedef struct s_parser
{
	t_msh	*msh;
	t_tok	*head;
	t_tok	*node;
	t_ast	*tmp;
}				t_parser;

typedef struct s_lexer
{
	t_msh	*msh;
	int		i;
	int		i_p;
	t_tok	*head;
	t_tok	*tail;
	char	*line;
}				t_lexer;

typedef struct s_we
{
	t_msh	*msh;
	t_ast	*curr;
	t_vec	*buff;
	char	*old;
	char	*ifs;
	int		type;
}				t_we;

/* ================================== LEXER ================================ */

/* FILE: src/parser/lexer1.c */

void	lexer(t_msh *msh);
void	lexer_handle_blank(t_lexer *lex);
void	lexer_handle_quote(t_lexer *lex);
int		lexer_handle_io_nbr(t_lexer *lex);
void	lexer_handle_io(t_lexer *lex);

/* FILE: src/parser/lexer2.c */

void	lexer_handle_pipe(t_lexer *lex);
void	lexer_new(t_lexer *lex, int type);
void	lexer_free(t_tok *head);
void	lexer_error(t_lexer *lex, char *msg);
void	lexer_print(t_tok *token);

/* ================================== PARSER ================================ */

/* FILE: src/parser/parser1.c */

void	parser(t_msh *msh);
t_ast	*parser_new(t_parser *vars, int type, t_tok *node);

/* FILE: src/parser/parser2.c */

t_ast	*parser_pipe(t_parser *vars);
t_ast	*parser_cmd_list(t_parser *vars);
t_ast	*parser_io_redir(t_parser *vars);
t_ast	*parser_io_file(t_parser *vars);
t_ast	*parser_io_here(t_parser *vars);

/* FILE: src/parser/parser3.c */

void	parser_free(t_ast *tree);
void	parser_error(t_parser *vars, char *msg, char *opt);
void	parser_print(t_ast *tree);

/* ============================= WORD EXPANSION ============================ */

/* FILE: src/parser/word_expansion1.c */

void	we_word_expansion(t_msh *msh);
void	we_ast_traversal(t_we *we, t_ast *curr);
void	we_lexeme_formating(t_we *we);
char	*we_param_expansion(t_we *we, char *lex, int state);
void	we_param_substitution(t_we *we, char *param, int state);

/* FILE: src/parser/word_expansion2.c */

void	we_error(t_we *we, char *msg);
void	we_add_word(t_we *we, t_vec *vec);

#endif
