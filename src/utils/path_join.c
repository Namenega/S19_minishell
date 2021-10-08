/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:18:03 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 12:26:05 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*path_join(char *dir, char *file)
{
	int		len_dir;
	int		len_file;
	char	*path;

	len_dir = ft_strlen(dir);
	len_file = ft_strlen(file);
	path = malloc(sizeof(*path) * (len_dir + len_file + 2));
	if (!path)
		return (NULL);
	ft_memcpy(path, dir, len_dir);
	path[len_dir] = '/';
	ft_memcpy(path + len_dir + 1, file, len_file);
	path[len_dir + 1 + len_file] = '\0';
	return (path);
}
