/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:41:04 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/24 17:28:36 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

int	utils_get_nbr_param_trav(t_cst *node, int nbr)
{
	if (node->type == CST_WORD)
		nbr++;
	if (node->left)
		nbr = utils_get_nbr_param_trav(node->left, nbr);
	if (node->right)
		nbr = utils_get_nbr_param_trav(node->right, nbr);
	return (nbr);
}

int	utils_get_nbr_param(t_cst *node)
{
	if (!node)
		return (0);
	return (utils_get_nbr_param_trav(node, 0));
}

void	launcher_error(t_exec *exec, char *msg)
{
	(void)exec;
	(void)msg;
}

void	launcher_set_exec(t_exec *exec, t_cst *cmd_root)
{
	
}

void	launcher_new_io(t_exec *exec, t_cst *io_redir)
{
	t_io	*new;

	if (io_redir->type != CST_IO_REDIR)
		return ;
	new = malloc(sizeof(*new));
	if (!new)
		launcher_error(exec, ERR_MALLOC);
	
}

void	launcher(t_msh *msh)
{
	t_exec	exec;

	if (!msh->root)
		return ;
	exec.argc = utils_get_nbr_param(msh->root);
	// exec.argv = malloc(sizeof(*exec.argv) * exec.argc);
	printf("nbr parameters: %i \n", exec.argc);
}