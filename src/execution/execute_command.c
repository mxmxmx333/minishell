/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:54:05 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/06 16:29:31 by nicvrlja         ###   ########.fr       */
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
	destroy_exe_path(msh);
}

int	execute_command(t_msh *msh, t_exec *current)
{
	pid_t	pid;

	pid = wrppd_fork(msh);
	if (is_parent(pid))
	{
		signal(SIGINT, SIG_IGN);
		msh->last_pid = pid;
		close_previous_pipe(msh, current);
	}
	else
	{
		signal(SIGINT, handle_sigint_child);
		signal(SIGQUIT, handle_sigquit);
		handle_redirections(msh, current);
		if (!ft_strnrealcmp(current->args[0], ".", 1) || !ft_strnrealcmp(current->args[0], "..", 2))
			error_complex(msh, CMDNF_ERR, current->args[0], 127);
		implement_command(msh, current);
		exit_success(msh);
	}
	return (0);
}
