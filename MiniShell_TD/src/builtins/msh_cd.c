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

# define DIRSEP		'/'
typedef struct stat		t_stat;

/*
** TODO:
**  - Check MAX_PATH only on input
**  - is "./..." absolute?
*/


// #define ELOOP			62	/* Too many levels of symbolic links */
// #define ENAMETOOLONG		63	/* File name too long */

#define	E_BASH		"msh: cd: "
#define	E_BASH_USE	": invalid option\ncd: usage: cd [dir]\n"
#define	E_BASH_HOME	"HOME not set\n"
#define	E_BASH_OPWD	"OLDPWD not set\n"
#define	E_BASH_SYM	": Too many levels of symbolic links\n"
#define	MSG_ENOENT	": No such file or directory\n"
#define	E_FILE_LONG	": File name too long\n"
#define EXIT_FAIL	1

int	path_is_absolute(char *str)
{
  if (str == 0 || str[0] == '\0')
	return (0);
  if (str[0] == '/')
	return (1);
  if (str[0] == '.' && (str[1] == '/' || str[1] == '\0'))
	return (1);
  if (str[0] == '.' && str[1] == '.' && (str[2] == '/' || str[2] == '\0'))
	return (1);
  return (0);
}

char	*get_absolute_path(char *cwd, char *dst)
{
	int		len_cwd;
	int		len_dst;
	char	*path;

	if (path_is_absolute(dst))
		return (ft_strdup(dst));
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
		return (path);
	}
}

int	msh_print_error(char *s1, char *s2, char *s3, int ret)
{
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
	return (ret);	
}


/*
** Return 1 if PATH corresponds to a directory. 
*/
int		msh_check_path (char *dst, char *path)
{
	t_stat	st;

	errno = 0;
	if (stat(path, &st))
	{
		if (errno == ENAMETOOLONG)
			return (msh_print_error(E_BASH, dst, E_FILE_LONG, EXIT_FAIL));
		if (errno == ELOOP)
			return (msh_print_error(E_BASH, dst, E_BASH_SYM, EXIT_FAIL));
		if (errno == ENOENT)
			return (msh_print_error(E_BASH, dst, E_BASH_SYM, EXIT_FAIL));
	}
	
	S_ISDIR (st.st_mode);

	if (ft_strlen(dst) > MAXPATHLEN)
		return (msh_print_error(E_BASH, dst, E_FILE_LONG, EXIT_FAIL));
}

static inline void	msh_canonpath_backtrack(char **p, char **q, char *base)
{
	(*p) += 2;
	if ((*q) > base)
	{
		while (--(*q)  > base && (*q)[0] != '/')
			;
	}
}
static inline void	msh_canonpath_cpy(char **p, char **q, char *base)
{
	if ((*q)  != base)
		*(*q) ++ = '/';
	while ((*p)[0] && (*p)[0] != '/')
		*(*q)++ = *(*p)++;
}

/*
** Return the canonical path from PATH:
** - Multiple '/'s are collapsed to a single '/'.
** - Leading './'s and trailing '/.'s are removed.
** - Trailing '/'s are removed.
** - Non-leading '../'s and trailing '..'s are handled by removing
**   portions of the path.
** Variables:
** - base points just past the root directory
** - p points at beginning of path element we're considering.
** - q points just past the last kept directory.
*/
char	*msh_canonpath(char *path)
{
	char	*result;
	char	*base;
	char	*p;
	char	*q;

	result = ft_strdup(path);
	if (!result)
		return (NULL);
	base = result + (result[0] == '/') + (result[1] == '/');
	p = base;
	q = base;
	while (p[0])
	{
		if (p[0] == '/')
			p++;
		else if(p[0] == '.' && (p[1] == '/' || p[1] == '\0'))
			p++;
		else if (p[0] == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0'))
			msh_canonpath_backtrack(&p, &q, base);
		else
			msh_canonpath_cpy(&p, &q, base);
	}
	q[0] = '\0';
	return (result);
}

int  msh_cd(t_msh *msh, int argc, char **argv, char **env)
{
	char	*path;
	t_vec	*buff;

	/* Opt handling */
	if (ft_strcmp(argv[1], "-") < 0)
		return (msh_print_error(E_BASH, argv[1], E_BASH_USE, EXIT_FAIL));
	/* Get dst*/
	if (!argv[1])
	{
		path = utils_env_get_param(env, "HOME", 4);
		if (!path)
			return (msh_print_error(E_BASH, E_BASH_HOME, NULL, EXIT_FAIL));
	}
	else if (argv[1][0]== '-' && argv[1][1] == '\0')
	{
		path = utils_env_get_param(env, "OLDPWD", 4);
		if (!path)
			return (msh_print_error(E_BASH, E_BASH_OPWD, NULL, EXIT_FAIL));
	}
	else
	{
		path = get_absolute_path(msh->cwd, argv[1]);
	}

	// concatenate: ABS = CWD + DST
	// Canonicalize CAN = canolize(ABS)
	// Check if PATH exist
	//	y-> use canonical CAN
	//	n-> try with ABS
	// Change directory: chdir()
	// Update PWD:
	//	- CAN: set PWD=CAn
	//	- ABS: uset getCWD
	/* Error Handling*/
	buff = ft_vec_new(2 * (MAXPATHLEN + 1));
	if (!buff)
		msh_error(msh, ERR_MALLOC);

}

char	*msh_chdir(t_msh *msh, char *dst)
{
	if (!msh->cwd)
		msh->cwd = get_cwd(NULL, 0);
}


// char	*msh_canonpath(char *path)
// {
// 	char	*result;
// 	char	*base;
// 	char	*p;
// 	char	*q;

// 	result = strdup(path);
// 	if (!result)
// 		return (NULL);
// 	base = result + 1;
// 	if (result[1] == '/')
// 		base++;
// 	p = base;
// 	q = base;
// 	while (p[0])
// 	{
// 		if (p[0] == '/')
// 			p++;
// 		else if(p[0] == '.' && (p[1] == '/' || p[1] == '\0'))
// 			p++;
// 		else if (p[0] == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0'))
// 		{
// 			p += 2;
// 			if (q > base)
// 			{
// 				while (--q > base && q[0] != '/')
// 					;
// 			}
// 		}
// 		else
// 		{
// 			if (q != base)
// 				*q++ = '/';
// 			while (p[0] && p[0] != '/')
// 				*q++ = *p++;
// 		}
// 	}
// 	q[0] = '\0';
// 	return (result);
// }
