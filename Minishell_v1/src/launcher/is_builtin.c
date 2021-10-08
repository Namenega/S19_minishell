/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:55:40 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 10:12:56 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static inline void	set_lowercase(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		s[i] = (s[i] | 0x20);
}

t_fct	is_builtin(char *name)
{
	set_lowercase(name);
	if (!ft_strncmp(name, "cd", 3))
		return (&msh_cd);
	else if (!ft_strncmp(name, "pwd", 4))
		return (&msh_pwd);
	else if (!ft_strncmp(name, "env", 4))
		return (&msh_env);
	else if (!ft_strncmp(name, "exit", 5))
		return (&msh_exit);
	else if (!ft_strncmp(name, "echo", 5))
		return (&msh_echo);
	else if (!ft_strncmp(name, "unset", 6))
		return (&msh_unset);
	else if (!ft_strncmp(name, "export", 4))
		return (&msh_export);
	else
		return (NULL);
}

// t_fct	is_builtin(char *name)
// {
// 	int					i;
// 	static t_builtin	lst[] = {
// 	{"cd", &msh_cd},
// 	{"pwd", &msh_pwd},
// 	{"env", &msh_env},
// 	{"exit", &msh_exit},
// 	{"echo", &msh_echo},
// 	{"unset", &msh_unset},
// 	{"export", &msh_export}
// 	};
// 	static int			max = sizeof(lst) / sizeof(t_builtin);

// 	set_lowercase(name);
// 	i = -1;
// 	while (++i < max)
// 	{
// 		if (!ft_strcmp(lst[i].name, name))
// 			break ;
// 	}
// 	if (i < max)
// 		return (lst[i].fct);
// 	return (NULL);
// }
