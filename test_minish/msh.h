/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:37:45 by namenega          #+#    #+#             */
/*   Updated: 2021/09/20 16:12:28 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes/libft/libft.h"

# define MS_BUFFER 1024
# define MS_TOK_SIZE 64
# define MS_TOK_DELIM " \t\r\n\a"

# define PIPE 10
# define GREAT 11
# define LESS 12
# define DGREAT 13
# define DLESS 14
# define WORD 15
# define IO_NUMBER 16
# define DOLLAR 17

typedef struct s_lsttok
{
	void				*content;
	int					tok_type;
	struct	s_lsttok	*next;
}				t_lsttok;


typedef struct s_token
{
	int			tokno;
	int			i;
	int			pos;
	t_lsttok	*lsttok;
}				t_token;

typedef t_lsttok t_tok;

/*
** MAIN_C
*/

int			main(int ac, char **av, char **envp);
void		ms_loop(void);

/*
** TOK_RECON_C
*/

t_lsttok	*tok_recon(char *line);
void		init_t_tok(t_token *tok);

/*
** UTILS_0_C
*/

int			isnt_special(char c);
void		free_token_list(t_token *tok);

/*
** TOKENS/IS_X_C
*/

void		is_pipe(char *line, t_token *tok);
void		is_less(char *line, t_token *tok);
void		is_more(char *line, t_token *tok);
void		is_quote(char *line, t_token *tok, char c);
void		is_word(char *line, t_token *tok);
void		is_io_number(t_token *tok);

/*
** FT_LST_C
*/

t_lsttok	*ft_lsttok_new(void *content, int type);
void		ft_lsttok_add_back(t_lsttok **alst, t_lsttok *new);
void		lst_new_addback(char *s, int type, t_token *tok);
void		ft_lsttok_clear(t_lsttok **lst, void (*del)(void *));

/*
** FT_LST_C
*/

void		ft_echo(t_token *tok);

#endif
