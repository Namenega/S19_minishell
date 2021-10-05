/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:02:44 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 16:20:33 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline size_t	get_size(char *path)
{
	size_t	size;

	size = 0;
	if (*path)
		size = 1;
	while (*path)
	{
		if (*path == ':')
			size++;
		path++;
	}
	return (size + 1);
}

static inline void	fill_path(t_msh *msh, char *path)
{
	size_t	i;
	char	*dir_s;
	char	*dir_e;

	i = 0;
	dir_s = path;
	dir_e = path;
	while (*dir_e)
	{
		if (*dir_e == ':')
		{
			*dir_e = '\0';
			msh->path[i] = ft_strdup(dir_s);
			if (!msh->path[i++])
				msh_error(msh, ERR_MALLOC);
			dir_s = dir_e + 1;
		}
		dir_e++;
	}
	msh->path[i] = ft_strdup(dir_s);
	if (!msh->path[i++])
		msh_error(msh, ERR_MALLOC);
	msh->path[i] = NULL;
}

void	set_path(t_msh *msh)
{
	char	*path;

	if (msh->path)
		free(msh->path);
	path = utils_env_get_param(msh->env, "PATH", 4);
	msh->path = malloc(sizeof(*msh->path) * (get_size(path)));
	if (!msh->path)
		msh_error(msh, ERR_MALLOC);
	fill_path(msh, path);
}
