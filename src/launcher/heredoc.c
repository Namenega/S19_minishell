/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 15:24:00 by namenega          #+#    #+#             */
/*   Updated: 2021/10/09 11:49:15 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern pid_t	g_sig;

void	hdoc_param_expansion(t_hdoc *hdoc)
{
	char	*ptr;
	char	*param;

	param = NULL;
	ptr = utils_env_check_name(++(hdoc->ptr_r));
	if (ptr)
	{
		param = msh_getenv(hdoc->msh->env, hdoc->ptr_r, ptr - hdoc->ptr_r);
		hdoc->ptr_r = ptr - 1;
	}
	else if (*hdoc->ptr_r == '?')
		param = hdoc->msh->ret;
	else
		*hdoc->buff->ptr++ = *(--(hdoc->ptr_r));
	if (!param)
		return ;
	if (ft_vec_check(hdoc->buff, param))
	{
		print_error(MSG_MSH, ERR_MALLOC, NULL, EXIT_FAILURE);
		return ;
	}
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
		hdoc->buff->ptr = hdoc->buff->str;
		hdoc->line = readline("heredoc> ");
		if (!hdoc->line || !ft_strcmp(hdoc->line, hdoc->eof))
			break ;
		if (ft_vec_check(hdoc->buff, hdoc->line))
		{
			print_error(MSG_MSH, ERR_MALLOC, NULL, EXIT_FAILURE);
			return ;
		}
		hdoc->ptr_r = hdoc->line;
		hdoc_if_dollar(hdoc);
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
	// signal(SIGINT, &handle_sigint);
	signal(SIGINT, SIG_DFL);
	read_heredoc(hdoc);
	close(hdoc->pipefd[1]);
	close(hdoc->pipefd[0]);
	exit(0);
}

int	heredoc(t_msh *msh, t_ast *ast)
{
	pid_t	pid;
	t_hdoc	hdoc;
	int		ret;

	hdoc.eof = ast->right->lex;
	hdoc.msh = msh;
	if (pipe(hdoc.pipefd) == -1)
		return (print_error(MSG_PIPE, strerror(errno), "\n", EXIT_FAILURE));
	pid = fork();
	if (pid < 0)
		return (print_error(MSG_FORK, strerror(errno), "\n", EXIT_FAILURE));
	if (pid == 0)
		pid_is_null(&hdoc);
	else
	{
		waitpid(pid, &ret, 0);
		close(hdoc.pipefd[1]);
		if (ret)
		{
			close(hdoc.pipefd[0]);
			return (-1);
		}
	}
	return (hdoc.pipefd[0]);
}
