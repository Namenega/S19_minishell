/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::	*/
/*	msh_cd.c											:+:	  :+:	:+:	*/
/*													+:+ +:+		 +:+	 */
/*	By: tderwedu <tderwedu@student.s19.be>		 +#+  +:+		+#+		*/
/*												+#+#+#+#+#+	+#+			*/
/*	Created: 2021/09/28 10:05:51 by tderwedu		  #+#	#+#			 */
/*	Updated: 2021/10/01 14:25:24 by tderwedu		 ###	########.fr		*/
/*																			*/
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include "utils.h"

typedef struct stat		t_stat;

/*
** TODO:
**  - Check MAX_PATH only on input
**  - is "./..." absolute?
*/

// #define ELOOP			62	/* Too many levels of symbolic links */
// #define ENAMETOOLONG		63	/* File name too long */

#define	MSH_CD			"msh: cd: "
#define	MSG_CD_USE		": invalid option\ncd: usage: cd [dir]\n"
#define	MSG_HOME		"HOME not set\n"
#define	MSG_OPWD		"OLDPWD not set\n"
#define	MSG_ELOOP		": Too many levels of symbolic links\n"
#define	MSG_ENOENT		": No such file or directory\n"
#define	MSG_ENAME2LONG	": File name too long\n"
#define MSG_ENOTDIR		": Not a directory\n"
#define EXIT_FAIL		1

int	msh_chdir(t_msh *msh, char *path)
{
	errno = 0;
	if (chdir(path))
		return (msh_print_error(MSH_CD, strerror(errno), NULL, EXIT_FAIL));
	// Update OLDPWD
	// Update PWD
	free(msh->cwd);
	msh->cwd = path;
	printf("   cwd:%s\n", msh->cwd);
	printf("getcwd:%s\n", getcwd(NULL, 0));
	return (0);
}

char	*get_absolute_path(char *cwd, char *dst)
{
	int		len_cwd;
	int		len_dst;
	char	*path;
	char	*canon_path;

	if (dst[0] == '/')
		path = ft_strdup(dst);
	else
	{
		len_cwd = ft_strlen(cwd);
		len_dst = ft_strlen(dst);
		path = malloc(sizeof(*path) * (len_cwd + len_dst + 1));
		if (!path)
			return (NULL);
		ft_memcpy(path, cwd, len_cwd);
		ft_memcpy(path + len_cwd, dst, len_dst);
		path[len_cwd + len_dst] = '\0';
	}
	canon_path = msh_canonpath(path);
	free(path);
	return (canon_path);
}

/*
** msh_check_path:
** Check if PATH is a valid path.
*/
int		msh_check_path(char *dst, char *path)
{
	t_stat	st;

	errno = 0;
	printf("OK OK OK \n");
	if (stat(path, &st))
	{
		if (errno == ENOENT)
			return (0);
		else if (errno == ENAMETOOLONG)
			return (msh_print_error(MSH_CD, dst, MSG_ENAME2LONG, EXIT_FAIL));
		else if (errno == ELOOP)
			return (msh_print_error(MSH_CD, dst, MSG_ELOOP, EXIT_FAIL));
		else if (!S_ISDIR (st.st_mode))
			return (msh_print_error(MSH_CD, dst, MSG_ENOTDIR, EXIT_FAIL));
		else
			return (msh_print_error(MSH_CD, strerror(errno), NULL, EXIT_FAIL));
	}
	if (ft_strlen(dst) > MAXPATHLEN)
		return (msh_print_error(MSH_CD, dst, MSG_ENAME2LONG, EXIT_FAIL));
	printf("OK OK OK \n");
	return (0);
}

int		msh_get_path(t_msh *msh, char *dst)
{
	char	*path;

	path = get_absolute_path(msh->cwd, dst);
	if (msh_check_path(dst, path))
		return (EXIT_FAIL);
	if (errno == ENOENT)
	{
		free(msh->cwd);
		msh->cwd = getcwd(NULL, 0);
		path = get_absolute_path(msh->cwd, dst);
		if (msh_check_path(dst, path))
			return (EXIT_FAIL);
		if (errno == ENOENT)
			return (msh_print_error(MSH_CD, dst, MSG_ENOENT, EXIT_FAIL));
	}
	return (msh_chdir(msh, path));
}

int  msh_cd(t_msh *msh, t_exec *exec)
{
	char	*path;

	printf("argv[1]:%s\n", exec->tab[1]);
	if (!exec->tab[1])
	{
		path = utils_env_get_param(exec->env, "HOME", 4);
		if (!path)
			return (msh_print_error(MSH_CD, MSG_HOME, NULL, EXIT_FAIL));
		return (msh_chdir(msh, path));
	}
	else if (exec->tab[1][0]== '-' && exec->tab[1][1] == '\0')
	{
		path = utils_env_get_param(exec->env, "OLDPWD", 4);
		if (!path)
			return (msh_print_error(MSH_CD, MSG_OPWD, NULL, EXIT_FAIL));
		return (msh_chdir(msh, path));
	}
	else if (exec->tab[1][0] == '-')
		return (msh_print_error(MSH_CD, exec->tab[1], MSG_CD_USE, EXIT_FAIL));
	else
		path = msh_get_path(msh, *(exec->tab));
	return (0);
}