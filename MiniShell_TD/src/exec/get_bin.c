/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:46:05 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 14:05:57 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/errno.h>

#include "minishell.h"

//	TODO: move to an HEADER
typedef struct dirent t_dirent;

static inline int	search_dir(t_msh *msh, char *file, char *path)
{
	int			found;
	DIR			*dirp;
	t_dirent	*info;

	found = 0;
	// printf("\033[33mDIR:%s\033[0m\n", path); 		// TODO:remove
	dirp = opendir(path);
	if (!dirp)
		msh_error(msh, strerror(errno));
	errno = 0;
	info = readdir(dirp);
	while (info && !found)
	{
		// printf("\033[35mFILE\033[0m:%s\n", info->d_name);	// TODO:remove
		if (ft_strcmp(file, info->d_name) == 0)
			found = 1;
		info = readdir(dirp);
	}
	closedir(dirp);
	if (errno)
		msh_error(msh, strerror(errno));
	return (found);
}

char	*get_bin(t_msh *msh, char *file)
{
	int		len_file;
	int		len_path;
	char	*filepath;
	char	**path;

	path = msh->path;
	while (*path)
	{
		if (search_dir(msh, file, *path))
			break ;
		path++;
	}
	if (!*path)
		return (NULL);
	len_path = ft_strlen(*path);
	len_file = ft_strlen(file);
	filepath = malloc(sizeof(*filepath) * (len_path + len_file + 2));
	if (!filepath)
		msh_error(msh, ERR_MALLOC);
	ft_memcpy(filepath, *path, len_path);
	filepath[len_path] = '/';
	ft_memcpy(filepath + len_path + 1, file, len_file);
	filepath[len_path + 1 + len_file] = '\0';
	return (filepath);
}
