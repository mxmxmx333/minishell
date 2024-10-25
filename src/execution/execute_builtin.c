/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:55:49 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/24 18:32:10 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_close(t_msh *msh, char *file)
{
	int	fd;

	fd = wrppd_open(msh, file, O_RDONLY);
	wrppd_close(msh, fd);
}

int	get_fd_output(t_msh *msh, t_tok *redirections)
{
	if (redirections->type == REDI_TOUT)
		return (wrppd_open(msh, redirections->file, O_TRUNC));
	else
		return (wrppd_open(msh, redirections->file, O_APPEND));
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
			open_close(msh, redirections->file);
		else
			fd = get_fd_output(msh, redirections);
		redirections = redirections->next;
	}
	if (exec->next)
	{
		msh->status = exec->builtin(msh, exec, exec->out_pipe[1]);
	}
	else
		msh->status = exec->builtin(msh, exec, fd);
}
