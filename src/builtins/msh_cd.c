/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:15:31 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/08 13:45:53 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	msh_chdir(t_msh *msh, char *path, int update)
{
	errno = 0;
	if (chdir(path))
		return (print_error(MSG_CD, strerror(errno), NULL, EXIT_FAILURE));
	if (msh_cd_export(msh, "OLDPWD", msh->cwd))
		return (EXIT_FAILURE);
	if (msh_cd_export(msh, "PWD", path))
		return (EXIT_FAILURE);
	free(msh->cwd);
	if (!update)
		msh->cwd = path;
	else
	{
		free(path);
		msh->cwd = getcwd(NULL, 0);
	}
	return (EXIT_SUCCESS);
}

char	*get_absolute_path(char *cwd, char *dst)
{
	int		len_cwd;
	int		len_dst;
	int		sep;
	char	*path;
	char	*canon_path;

	if (dst[0] == '/')
		path = ft_strdup(dst);
	else
	{
		len_cwd = ft_strlen(cwd);
		len_dst = ft_strlen(dst);
		sep = (len_cwd > 2 || (len_cwd == 2 && cwd[1] != '/'));
		path = malloc(sizeof(*path) * (len_cwd + sep + len_dst + 1));
		if (!path)
			return (NULL);
		ft_memcpy(path, cwd, len_cwd);
		if (sep)
			path[len_cwd] = '/';
		ft_memcpy(path + len_cwd + sep, dst, len_dst);
		path[len_cwd + sep + len_dst] = '\0';
	}
	canon_path = msh_canonpath(path);
	free(path);
	return (canon_path);
}

int	msh_check_path(char *dst, char *path)
{
	t_stat	st;

	errno = 0;
	if (stat(path, &st))
	{
		if (errno == ENOENT || errno == ELOOP)
			return (0);
		else if (errno == ENAMETOOLONG)
			return (print_error(MSG_CD, dst, ERR_ENAME2LONG, EXIT_FAILURE));
		else if (!S_ISDIR (st.st_mode))
			return (print_error(MSG_CD, dst, ERR_ENOTDIR, EXIT_FAILURE));
		else
			return (print_error(MSG_CD, strerror(errno), NULL, EXIT_FAILURE));
	}
	if (ft_strlen(dst) > MAXPATHLEN)
		return (print_error(MSG_CD, dst, ERR_ENAME2LONG, EXIT_FAILURE));
	return (0);
}

int	msh_set_path(t_msh *msh, char *dst)
{
	int		update;
	char	*path;

	path = get_absolute_path(msh->cwd, dst);
	if (msh_check_path(dst, path))
		return (EXIT_FAILURE);
	update = (errno == ELOOP);
	if (errno == ENOENT || errno == ELOOP)
	{
		free(msh->cwd);
		msh->cwd = getcwd(NULL, 0);
		path = get_absolute_path(msh->cwd, dst);
		if (msh_check_path(dst, path))
			return (EXIT_FAILURE);
		if (errno == ENOENT)
			return (print_error(MSG_CD, dst, ERR_ENOENT, EXIT_FAILURE));
		else if (errno == ELOOP)
			return (print_error(MSG_CD, dst, ERR_ELOOP, EXIT_FAILURE));
	}
	return (msh_chdir(msh, path, update));
}

int	msh_cd(t_exec *exec)
{
	char	*path;

	if (!exec->argv[1])
	{
		path = msh_getenv(exec->msh->env, "HOME", 4);
		if (!path)
			return (print_error(MSG_CD, ERR_HOME, NULL, EXIT_FAILURE));
		return (msh_set_path(exec->msh, path));
	}
	else if (exec->argv[1][0] == '-' && exec->argv[1][1] == '\0')
	{
		path = msh_getenv(exec->msh->env, "OLDPWD", 4);
		if (!path)
			return (print_error(MSG_CD, ERR_OLDPWD, NULL, EXIT_FAILURE));
		return (msh_set_path(exec->msh, path));
	}
	else if (exec->argv[1][0] == '-')
		return (print_error(MSG_CD, exec->argv[1], ERR_CD_USE, EXIT_FAILURE));
	else
		return (msh_set_path(exec->msh, exec->argv[1]));
}
