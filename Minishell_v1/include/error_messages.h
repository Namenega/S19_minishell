/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:25:07 by namenega          #+#    #+#             */
/*   Updated: 2021/10/08 13:36:03 by namenega         ###   ########.fr       */
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
# define MSG_FORK		"msh: fork: "
# define MSG_OPEN		"msh: open: "
# define MSG_PIPE		"msh: pipe: "
# define MSG_EXECVE		"msh: execve: "
# define MSG_EXPORT		"msh: export: `"
# define MSG_UNSET		"msh: unset: `"
# define ERR_MALLOC		"Malloc error."
# define ERR_NO_CMD		"msh: %s: command not found\n"		// TODO: replace with print_error
# define ERR_QUOTES		"msh: error odd number of quotes."
# define ERR_SYNTAX		"Syntax Error near: %s\n"			// TODO: replace with print_error
# define MSG_CD_USE		": invalid option\ncd: usage: cd [dir]\n"
# define MSG_ELOOP		": Too many levels of symbolic links\n"
# define MSG_ENAME2LONG	": File name too long\n"
# define MSG_EXIT		"msh: exit: "
# define MSG_EXIT_ARGS	"too many arguments\n"
# define MSG_EXIT_USE	": numeric argument required\n"
# define MSG_ENOENT		": No such file or directory\n"
# define MSG_ENOTDIR	": Not a directory\n"
# define MSG_HOME		"HOME not set\n"
# define MSG_IDENTIFIER	"': not a valid identifier\n"
# define MSG_NOTFOUND	": command not found\n"
# define MSG_OLDPWD		"OLDPWD not set\n"
# define MSG_ARGC		"Wrong number of argument\n"

#endif
