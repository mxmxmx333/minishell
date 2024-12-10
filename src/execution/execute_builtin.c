/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:55:49 by mbonengl          #+#    #+#             */
/*   Updated: 2024/12/10 11:44:49 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_close(t_msh *msh, char *file)
{
	int	fd;

	fd = wrppd_open_builtin(msh, file, O_RDONLY);
	wrpped_close_builtin(msh, fd);
}

static int	get_fd_out(t_msh *msh, t_tok *redirections, int current, int pipe)
{
	if (current != 1 && current != pipe)
		wrpped_close_builtin(msh, current);
	if (redirections->type == REDI_TOUT)
		return (wrppd_open_builtin(msh, redirections->file, O_TRUNC));
	else
		return (wrppd_open_builtin(msh, redirections->file, O_APPEND));
}

static int	redi_status(t_msh *msh, t_tok *redirections, int *fd, int pipefd)
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
			*fd = get_fd_out(msh, redirections, *fd, pipefd);
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
	int		pipefd;

	fd = 1;
	redirections = exec->redirections;
	if (exec->next)
		fd = exec->out_pipe[1];
	pipefd = fd;
	if (redi_status(msh, redirections, &fd, pipefd))
		return ;
	msh->status = exec->builtin(msh, exec, fd);
	if (fd != 1 && fd != pipefd)
		wrpped_close_builtin(msh, fd);
}
