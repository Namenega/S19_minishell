/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:25:07 by namenega          #+#    #+#             */
/*   Updated: 2021/10/05 14:58:53 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# define ERR_MALLOC "Malloc error."
# define ERR_NO_CMD "msh: %s: command not found\n"
# define ERR_QUOTES "msh: error odd number of quotes."
# define ERR_SYNTAX "Syntax Error near: %s\n"
# define MSG_CD "msh: cd: "
# define MSG_EXPORT "msh: export: `"
# define MSG_BASH "msh: "
# define MSG_CD_USE ": invalid option\ncd: usage: cd [dir]\n"
# define MSG_ELOOP ": Too many levels of symbolic links\n"
# define MSG_ENAME2LONG ": File name too long\n"
# define MSG_EXIT "msh: exit: "
# define MSG_EXIT_ARGS "too many arguments\n"
# define MSG_EXIT_USE ": numeric argument required\n"
# define MSG_ENOENT ": No such file or directory\n"
# define MSG_ENOTDIR ": Not a directory\n"
# define MSG_HOME "HOME not set\n"
# define MSG_IDENTIFIER "': not a valid identifier\n"
# define MSG_NOTFOUND ": command not found\n"
# define MSG_OLDPWD "OLDPWD not set\n"
# define EXIT_FAIL 1

#endif