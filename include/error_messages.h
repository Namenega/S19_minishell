/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:25:07 by namenega          #+#    #+#             */
/*   Updated: 2021/10/08 18:14:01 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# define ERRNO_NOT_FOUND	127

// Choose between ERR and MSG
# define MSG_MSH		"msh: "
# define MSG_CD			"msh: cd: "
# define MSG_DUP		"msh: dup: "
# define MSG_DUP2		"msh: dup2: "
# define MSG_EXIT		"msh: exit: "
# define MSG_FORK		"msh: fork: "
# define MSG_OPEN		"msh: open: "
# define MSG_PIPE		"msh: pipe: "
# define MSG_EXECVE		"msh: execve: "
# define MSG_EXPORT		"msh: export: `"
# define MSG_UNSET		"msh: unset: `"
# define ERR_MALLOC		"Malloc error\n"
# define ERR_QUOTES		"Odd number of quotes\n"
# define ERR_SYNTAX		"Syntax Error near: "
# define ERR_CD_USE		": invalid option\ncd: usage: cd [dir]\n"
# define ERR_ELOOP		": Too many levels of symbolic links\n"
# define ERR_EXIT_ARGS	"too many arguments\n"
# define ERR_NOTFOUND	": command not found\n"
# define ERR_EXIT_USE	": numeric argument required\n"
# define ERR_ENOENT		": No such file or directory\n"
# define ERR_ENOTDIR	": Not a directory\n"
# define ERR_HOME		"HOME not set\n"
# define ERR_ENAME2LONG	": File name too long\n"
# define ERR_IDENTIFIER	"': not a valid identifier\n"
# define ERR_OLDPWD		"OLDPWD not set\n"
# define ERR_ARGC		"Wrong number of argument\n"

#endif
