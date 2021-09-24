/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:01:30 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/24 15:56:24 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "vector.h" // TODO: Add to libft
# include "lexer.h"
# include "parser.h"
# include "word_expansion.h"


/*
** FILE: utils.c
*/

void	msh_error(t_msh *msh, char *msg);

/*
** FILE: utils_env.c
*/

char	*utils_env_get_ifs(char **env);
char	*utils_env_check_name(char *str);
char	*utils_env_get_param(char **env, char *var, int len);

#endif