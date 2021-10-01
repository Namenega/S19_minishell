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

// #define ELOOP			62			  /* Too many levels of symbolic links */
// #define ENAMETOOLONG	63			  /* File name too long */

int	path_isabsolute(char *str)
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

/*
** Return 1 if PATH corresponds to a directory. 
*/
static int	msh_isdir (char *path)
{
	t_stat	sb;

	return (stat (path, &sb) == 0 && S_ISDIR (sb.st_mode));
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
		*(*q) ++ = *(*p)++;
}

/*
** Return the canonical path from PATH:
** - Multiple '/'s are collapsed to a single '/'.
** - Leading './'s and trailing '/.'s are removed.
** - Trailing '/'s are removed.
** - Non-leading '../'s and trailing '..'s are handled by removing
**   portions of the path.
** Variables:
** - base ust past the root directory
** - p points at beginning of path element we're considering.
** - q points just past the last kept directory.
**/
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
	char	*dst;
	t_vec	*buff;

	/* Opt handling */
	if (ft_strcmp(argv[1], "-") < 0)
	{
		write(2, "msh: cd: ", 9);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": invalid option\ncd: usage: cd [dir]\n", 37);
		return (EXIT_FAILURE);
	}
	/* Get dst*/
	if (!argv[1])
	{
		dst = utils_env_get_param(env, "HOME", 4);
		if (!dst)
		{
				write(2, "msh: cd: HOME not set\n", 22);
				return (EXIT_FAILURE);
		}
	}
	else if (argv[1][0]== '-' && argv[1][1] == '\0')
	{
		dst = utils_env_get_param(env, "OLDPWD", 4);
		if (!dst)
		{
				write(2, "msh: cd: OLDPWD not set\n", 24);
				return (EXIT_FAILURE);
		}
	}
	else
		dst = argv[1];

	// concatenate: ABS = CWD + DST
	// Canonicalize CAN = canolize(ABS)
	// Check if PATH exist
	//	y-> use canonical CAN
	//	n-> try with ABS
	// Change directory: chdir()
	// Update PWD:
	//	- CAN: set PWD=CAn
	//	- ABS: uset getCWD
	
	if (dst > MAXPATHLEN)
	{
		write(2, "msh: cd: ", 9);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": File name too long\n", 21);
	}
	/* Error Handling*/
	buff = ft_vec_new(2 * (MAXPATHLEN + 1));
	if (!buff)
		msh_error(msh, ERR_MALLOC);
	ft_strcpy();

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
