/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:33:45 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/27 14:41:26 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_H
# define WORD_EXPANSION_H

# include "libft.h"

// TODO: Add 'vector.h' to libft
# include "vector.h"
# include "minishell.h"
# include "parser.h"
# include "utils.h"

// # include "msh_error.h"

// TODO: all ERR in ine header
# define ERR_MALLOC		"Malloc error."

# define TYPE_IO	0
# define TYPE_CMD	1

typedef struct s_tok	t_tok;
typedef struct s_cst	t_cst;
typedef struct s_msh	t_msh;

enum	e_we_st
{
	WE_ST_FREE,
	WE_ST_SQUOTE,
	WE_ST_DQUOTE
};

typedef struct s_we
{
	t_msh	*msh;
	t_cst	*curr;
	t_vec	*buff;
	char	*old;
	char	*ifs;
	int		type;
}				t_we;

/*
** FILE: word_expansion1.c
*/

void	we_word_expansion(t_msh *msh);
void	we_cst_traversal(t_we *we, t_cst *curr);
void	we_lexeme_formating(t_we *we);
char	*we_param_expansion(t_we *we, char *lex, int state);
void	we_param_substitution(t_we *we, char *param, int state);

/*
** FILE: word_expansion2.c
*/

void	we_error(t_we *we, char *msg);
void	we_add_word(t_we *we, t_vec *vec);

#endif
