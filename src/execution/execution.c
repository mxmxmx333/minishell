/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:55:24 by mbonengl          #+#    #+#             */
/*   Updated: 2024/12/10 11:09:44 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	wait_for_child(t_msh *msh)
{
	int	*status;

	status = &msh->status;
	while (wait(status) != msh->last_pid)
		;
	if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGINT)
			handle_sigint_child(0);
		if (WTERMSIG(*status) == SIGQUIT)
			handle_sigquit(0);
	}
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	while (wait(NULL) > 0)
		;
}

/* 
	exit point for the execution, destroys all the generated assets 
*/
void	finished_execution(t_msh *msh)
{
	destroy_exp(msh);
	destroy_paths(msh);
	destroy_executable(msh);
	signal(SIGINT, handle_sigint);
}

/* 
	entry point for the execution, generates the neccesairy assets 
*/
void	prepare_execution(t_msh *msh)
{
	destroy_exp(msh);
	convert_exp(msh);
	extract_paths(msh);
}

/*

*/
int	execution(t_msh *msh)
{
	t_exec	*current;

	current = msh->exec_table;
	prepare_execution(msh);
	set_all_builtins(current);
	if (!current->next && current->builtin)
		execute_builtin(msh, current);
	else
	{
		while (current)
		{
			create_out_pipe(msh, current);
			execute_command(msh, current);
			if (!current->next)
				break ;
			current = current->next;
		}
	}
	if (current->prev || !current->builtin)
		wait_for_child(msh);
	finished_execution(msh);
	return (0);
}
