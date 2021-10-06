/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 15:24:00 by namenega          #+#    #+#             */
/*   Updated: 2021/10/06 17:03:53 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

extern pid_t	g_sig;

//CTRL C need to stop process
//CTRL D need to stop process but print readline buffer already registered.

typedef struct s_hdoc
{
	int		pipefd[2];
	char	*line;
	char	*eof;
}				t_hdoc;

char *hdoc_param_expansion(char *line, t_we *we, int state)
{
	char *ptr;
	char *param;

	ptr = utils_env_check_name(line + 1);
	if (ptr)
	{
		param = utils_env_get_param(we->msh->env, line + 1, ptr - (line + 1));
		line = ptr - 1;
		if (param)
			we_param_substitution(we, param, state);
	}
	return (line);
}

static void	read_heredoc(t_hdoc *hdoc, t_we *we)
{
	int	i;
	int	state;

	i = 0;
	state = WE_ST_FREE;
	printf("3\n");
	while (1)
	{
		hdoc->line = readline("heredoc> ");
		if (!hdoc->line || !ft_strcmp(hdoc->line, hdoc->eof))
			break ;
		we->buff = ft_vec_new(DFLT_VEC_SIZE);
		if (ft_vec_check(we->buff, hdoc->line))
			we_error(we, ERR_MALLOC);
		while (hdoc->line[i])
		{
			if (hdoc->line[i] == '$' && state != WE_ST_SQUOTE)
				hdoc->line = hdoc_param_expansion(hdoc->line, we, state);
			i++;
		}
		write(hdoc->pipefd[1], hdoc->line, ft_strlen(hdoc->line));
		write(hdoc->pipefd[1], "\n", 1);
	}
}

int	heredoc(t_msh *msh, t_ast *ast, t_we *we)
{
	pid_t	pid;
	t_hdoc	*hdoc;
	int		ret;

	(void)msh;
	hdoc = malloc(sizeof(t_hdoc));
	hdoc->eof = ast->right->lex;
	printf("1\n");
	if (pipe(hdoc->pipefd) == -1)
		return (0);					//!Error msg need to change : pipe error.
	pid = fork();
	if (pid < 0)
		return (0);					//!Error msg need to change : fork error.
	if (pid == 0)
	{
		printf("2\n");
		g_sig = 1;
		signal(SIGINT, SIG_DFL);
		read_heredoc(hdoc, we);
		free(hdoc->line);
		close(hdoc->pipefd[1]);
		close(hdoc->pipefd[0]);
		exit(0);					//! Error need to change
	}
	else
	{
		waitpid(pid, &ret, 0);
		close(hdoc->pipefd[1]);
		// ret = WEXITSTATUS(ret);
		if (ret != EXIT_SUCCESS)
		{
			close(hdoc->pipefd[0]);
			return (-1);
		}
	}
	// printf("PIPE[0]:%i\n", pipefd[0]);
	// printf("PIPE[1]:%i\n", pipefd[1]);
	return (hdoc->pipefd[0]);
}
