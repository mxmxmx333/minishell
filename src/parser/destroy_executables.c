/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_executables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:10:27 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/23 15:22:05 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_executable_2(t_msh *msh)
{
	t_exec	*tmp;
	t_tok	*deleteme;

	while (msh->exec_table)
	{
		tmp = msh->exec_table;
		msh->exec_table = msh->exec_table->next;
		if (tmp->args)
			destroy_str_array(tmp->args);
		if (tmp->redirections)
		{
			while (tmp->redirections)
			{
				deleteme = tmp->redirections;
				tmp->redirections = tmp->redirections->next;
				destroy_tok_node(NULL, deleteme);
			}
		}
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->builtin)
			free(tmp->builtin);
		free(tmp);
	}
	msh->exec_table = NULL;
}

void	destroy_executable(t_msh *msh)
{
	t_exec	*tmp;

	tmp = msh->exec_table;
	while (tmp)
	{
		if (tmp->pipe)
		{
			close_pipe(msh, tmp->out_pipe);
			tmp->pipe = false;
		}
		tmp = tmp->next;
	}
	destroy_executable_2(msh);
}
