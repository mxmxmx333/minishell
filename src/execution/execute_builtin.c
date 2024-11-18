/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:55:49 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/13 14:25:04 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_close(t_msh *msh, char *file)
{
	int	fd;

	fd = wrppd_open_builtin(msh, file, O_RDONLY);
	wrpped_close_builtin(msh, fd);
}

int	get_fd_output(t_msh *msh, t_tok *redirections)
{
	if (redirections->type == REDI_TOUT)
		return (wrppd_open_builtin(msh, redirections->file, O_TRUNC));
	else
		return (wrppd_open_builtin(msh, redirections->file, O_APPEND));
}

int	redi_status(t_msh *msh, t_tok *redirections, int *fd)
{
	while (redirections)
	{
		if (redirections->type != HERE_DOC && (redirections->splitfile
											|| redirections->lonely))
		{
			msh->status = 1;
			dis_func_err(msh, "", redirections->file, "ambiguous redirect");
			return (1);
		}
		if (redirections->type == REDI_IN || redirections->type == HERE_DOC)
			open_close(msh, redirections->file);
		else
			*fd = get_fd_output(msh, redirections);
		redirections = redirections->next;
		if (msh->status)
			return (1);
	}
	return (0);
}

void	execute_builtin(t_msh *msh, t_exec *exec)
{
	t_tok	*redirections;
	int		fd;
	
	fd = 1;
	redirections = exec->redirections;
	if (exec->next)
		fd = exec->out_pipe[1];
	if (redi_status(msh, redirections, &fd))
		return ;
	msh->status = exec->builtin(msh, exec, fd);
}
