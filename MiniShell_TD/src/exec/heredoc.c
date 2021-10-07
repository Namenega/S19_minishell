/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 15:24:00 by namenega          #+#    #+#             */
/*   Updated: 2021/10/07 17:48:49 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sys/wait.h>
#include <sys/types.h>
#include "../../include/exec.h"

extern pid_t	g_sig;

//*COMPARE TO BASH
//BUG 1 : ctrl+C doesnt work properly
//BUG 2 : CTRL+D doesnt work properly
//BUG 3 : $'USER' et $"USER"



//CTRL C need to stop process
//CTRL D need to stop process but print readline buffer already registered.
//OUR CTRL D write buffer on a new line because of readline !

void	hdoc_param_expansion(t_hdoc *hdoc)
{
	char	*ptr;
	char	*param;

	param = NULL;
	// if (*++hdoc->ptr_r == '\'' || *hdoc->ptr_r == '\"')
	// 	return ;
	ptr = utils_env_check_name(++(hdoc->ptr_r));
	if (ptr)
	{
		param = utils_env_get_param(hdoc->msh->env, hdoc->ptr_r, ptr - hdoc->ptr_r);
		hdoc->ptr_r = ptr - 1; // -1 a cause du hdoc->ptr_r++ de read_heredoc
	}
	else if (*hdoc->ptr_r == '?' )
		param = hdoc->msh->ret;
	if (!param)
		return ;
	if (ft_vec_check(hdoc->buff, param))
		return ; // TODO: hdoc_error which call ft_free_vec and msh_error
	while (*param)
		*hdoc->buff->ptr++ = *param++;
}

static void	hdoc_if_dollar(t_hdoc *hdoc)
{
	while (*hdoc->ptr_r)
	{
		if (*hdoc->ptr_r == '$' && (*(hdoc->ptr_r + 1) == '\''
			|| *(hdoc->ptr_r + 1) == '\"'))
			*hdoc->buff->ptr++ = *hdoc->ptr_r;
		else if (*hdoc->ptr_r == '$')
			hdoc_param_expansion(hdoc);
		else
			*hdoc->buff->ptr++ = *hdoc->ptr_r;
		hdoc->ptr_r++;
	}
}

static void	read_heredoc(t_hdoc *hdoc)
{
	hdoc->buff = ft_vec_new(DFLT_VEC_SIZE);
	while (1)
	{
		hdoc->buff->ptr = hdoc->buff->str; // reset vec
		hdoc->line = readline("heredoc> ");
		if (!hdoc->line || !ft_strcmp(hdoc->line, hdoc->eof))
			break ;
		if (ft_vec_check(hdoc->buff, hdoc->line))
			return ;	// TODO: hdoc_error which call ft_free_vec and msh_error
		hdoc->ptr_r = hdoc->line;
		hdoc_if_dollar(hdoc);
		// while (*hdoc->ptr_r)
		// {
		// 	if (*hdoc->ptr_r == '$')
		// 		hdoc_param_expansion(hdoc);
		// 	else
		// 		*hdoc->buff->ptr++ = *hdoc->ptr_r;
		// 	hdoc->ptr_r++;
		// }
		*hdoc->buff->ptr = '\0';
		write(hdoc->pipefd[1], hdoc->buff->str, ft_strlen(hdoc->buff->str));
		write(hdoc->pipefd[1], "\n", 1);
	}
	free(hdoc->line);
	ft_vec_free(hdoc->buff);
}

static void	pid_is_null(t_hdoc *hdoc)
{
	g_sig = 1;
	signal(SIGINT, SIG_DFL);
	read_heredoc(hdoc);
	close(hdoc->pipefd[1]);
	close(hdoc->pipefd[0]);
	exit(0);					//! Error need to change
}

int	heredoc(t_msh *msh, t_ast *ast)
{
	pid_t	pid;
	t_hdoc	hdoc;
	int		ret;

	hdoc.eof = ast->right->lex;
	hdoc.msh = msh;
	if (pipe(hdoc.pipefd) == -1)
		return (0);					//!Error msg need to change : pipe error.
	pid = fork();
	if (pid < 0)
		return (0);					//!Error msg need to change : fork error.
	if (pid == 0)
		pid_is_null(&hdoc);
	else
	{
		waitpid(pid, &ret, 0);
		close(hdoc.pipefd[1]);
		// ret = WEXITSTATUS(ret);
		if (ret != EXIT_SUCCESS)
		{
			close(hdoc.pipefd[0]);
			return (-1);
		}
	}
	return (hdoc.pipefd[0]);
}
