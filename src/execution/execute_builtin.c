/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:55:49 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/06 17:52:26 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_builtin(t_exec *exec)
{
	set_builtin_function(exec);
	if (exec->builtin)
		return (1);
	return (0);
}

static int open_close(t_msh *msh, char *file)
{
	int	fd;

	fd = wrppd_open_builtin(msh, file, O_RDONLY);
	if (fd == -1)
	{
		msh->status = 1;
		return (1);
	}
	wrppd_close(msh, fd);
	return (0);
}

int	get_fd_output(t_msh *msh, t_tok *redirections)
{
	if (redirections->type == REDI_TOUT)
		return (wrppd_open_builtin(msh, redirections->file, O_TRUNC));
	else
		return (wrppd_open_builtin(msh, redirections->file, O_APPEND));
}

void	run_builtin(t_msh *msh, t_exec *exec, int fd)
{
	if (exec->next && !is_builtin(exec->next))
	{
		if (exec->builtin != command_export)
			msh->status = exec->builtin(msh, exec, exec->out_pipe[1]);
	}
	else if (exec->next && is_builtin(exec->next) && fd != STDOUT_FILENO)
		msh->status = exec->builtin(msh, exec, fd);
	else if (!exec->next)
		msh->status = exec->builtin(msh, exec, fd);
}

void	execute_builtin(t_msh *msh, t_exec *exec)
{
	t_tok	*redirections;
	int		fd;
	
	fd = 1;
	redirections = exec->redirections;
	while (redirections)
	{
		if (redirections->type == REDI_IN || redirections->type == HERE_DOC)
		{
			if (open_close(msh, redirections->file))
				return ;
		}
		else
		{
			fd = get_fd_output(msh, redirections);
			if (fd == -1)
			{
				msh->status = 1;
				return ;
			}
		}
		redirections = redirections->next;
	}
	run_builtin(msh, exec, fd);
	wrpped_close_builtin(msh, fd);
}
