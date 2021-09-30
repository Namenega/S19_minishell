/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:01:30 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/30 10:19:06 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "parser.h"
# include "minishell.h"

typedef struct s_tok	t_tok;
typedef struct s_ast	t_ast;
typedef struct s_msh	t_msh;

/*
** FILE: utils.c
*/

void	msh_error(t_msh *msh, char *msg);
int		ret_str_2_int(t_msh *msh);
void	ret_int_2_str(t_msh *msh, int ret);

/*
** FILE: utils_env.c
*/

void	utils_env_sort(char **env);
void	utils_free_tab(char **env);
size_t	utils_env_size(char **env);
void	utils_env_print(char **tab);
char	**utils_env_copy(char **env, size_t size);
char	*utils_env_get_ifs(char **env);
char	*utils_env_check_name(char *str);
char	*utils_env_get_param(char **env, char *var, int len);

#endif