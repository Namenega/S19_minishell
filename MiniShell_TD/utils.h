/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:01:30 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/27 14:41:37 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "vector.h" // TODO: Add to libft
# include "lexer.h"
# include "parser.h"
# include "word_expansion.h"

typedef struct s_tok	t_tok;
typedef struct s_cst	t_cst;
typedef struct s_msh	t_msh;

/*
** FILE: utils.c
*/

void	msh_error(t_msh *msh, char *msg);

/*
** FILE: utils_env.c
*/

void	utils_env_free(char **env);
size_t	utils_env_size(char **env);
char	**utils_env_copy(char **env, size_t size);
char	*utils_env_get_ifs(char **env);
char	*utils_env_check_name(char *str);
char	*utils_env_get_param(char **env, char *var, int len);

#endif