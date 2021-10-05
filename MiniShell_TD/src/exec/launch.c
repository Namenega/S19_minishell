/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:23:31 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 15:27:35 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

void	msh_launch(t_msh *msh)
{
	int		pipe_in[2];
	int		pipe_out[2];
	t_exec	*exec;
	t_ast	*cmd;

	cmd = msh->ast;
	if (cmd->type == AST_PIPE)
	{
		
	}
	while (cmd)
	{
		
	}
	if (msh->ast->type == AST_PIPE)
			exec = cmd_get(&msh, msh->ast->left);
	else
		exec = cmd_get(&msh, msh->ast);
		which_cmd(&msh, exec);
}