/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:37:45 by namenega          #+#    #+#             */
/*   Updated: 2021/09/28 16:17:09 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../includes/libft/libft.h"

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
	void			*content;
	int				tok_type;
	struct s_lsttok	*next;
}				t_lsttok;

typedef struct s_token
{
	int			tokno;
	int			i;
	int			pos;
	char		*tmp;
	t_lsttok	*lsttok;
}				t_token;

typedef t_lsttok	t_tok;

typedef struct s_io
{
	int			fd;
	int			oflag;
	char		*filename;
	struct t_io	*next;
}				t_io;


typedef struct s_launch
{
	int			size;
	char		**tab;
	char		**env;
	t_io		*io;
	// t_fd		*pipe_in;
	// t_fd		*pipe_out;
}				t_launch;

/*
** MAIN_C
*/

int			main(int ac, char **av, char **envp);
void		ms_loop(void);

/*
** UTILS_0_C
*/

int			isnt_special(char c);
void		free_token_list(t_token *tok);

/*
** TOKENS/TOK_RECON_C
** TOKENS/IS_QUOTE_C
** TOKENS/IS_IO_C
** TOKENS/IS_PIPE_C
*/

t_lsttok	*tok_recon(char *line);
void		init_t_tok(t_token *tok, char *line);
void		new_tok(t_token *tok, int type);
void		is_space(t_token *tok);
void		is_quote(t_token *tok);
void		is_io(t_token *tok);
int			check_io(t_token *tok);
void		is_pipe(t_token *tok);

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

/*
** FT_ECHO_C
*/

void		ft_echo(t_token *tok);
void		skip_quote(char *s, int c, int d);

#endif
