/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:54:05 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/31 14:53:23 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirections(t_msh *msh, t_exec *current)
{
	t_tok	*redirections;

	redirections = current->redirections;
	redirect_inpipe(msh, current);
	while (redirections)
	{
		if (redirections->type == REDI_IN || redirections->type == HERE_DOC)
		{
			redirect_input(msh, redirections);
		}
		else
			redirect_output(msh, redirections);
		redirections = redirections->next;
	}
	redirect_outpipe(msh, current);
	close_both_pipes(msh, current);
}

void	implement_command(t_msh *msh, t_exec *current)
{
	if (!current->args || !current->args[0])
		return ;
	pathfinder(msh, current->args[0]);
	execve(msh->exe_path, current->args, msh->export);
	free(msh->exe_path);
}

int	execute_command(t_msh *msh, t_exec *current)
{
	pid_t	pid;

	pid = wrppd_fork(msh);
	if (is_parent(pid))
	{
		msh->last_pid = pid;
		close_previous_pipe(msh, current);
	}
	else
	{
		handle_redirections(msh, current);
		implement_command(msh, current);
		exit_success(msh);
	}
	return (0);
}
