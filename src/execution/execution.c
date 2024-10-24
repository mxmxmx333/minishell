/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:55:24 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/24 18:32:20 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* 
	exit point for the execution, destroys all the generated assets 
*/
void	finished_execution(t_msh *msh)
{
	destroy_exp(msh);
	destroy_paths(msh);
	destroy_executable(msh);
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

	prepare_execution(msh);
	current = msh->exec_table;
	while (current)
	{
		create_out_pipe(msh, current);
		set_builtin_function(current);
		if (current->builtin && current->prev && current->prev->builtin)
			wrppd_close(msh, current->prev->out_pipe[0]);
		if (current->builtin)
			execute_builtin(msh, current);
 		else
			execute_command(msh, current);
		current = current->next;
	}
	while (wait(NULL) >	0) //FIXME: this is a temporary solution
		;
	finished_execution(msh);
	return (0);
}
