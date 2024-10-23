/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:30:03 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/23 15:32:05 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(t_msh *msh, t_tok *redirections)
{
	int	fd;

	fd = wrppd_open(msh, redirections->content, O_RDONLY);
	wrppd_dup2(msh, fd, STDIN_FILENO);
	wrppd_close(msh, fd);
}

void	redirect_output(t_msh *msh, t_tok *redirections)
{
	int	fd;

	if (redirections->type == REDI_TOUT)
		fd = wrppd_open(msh, redirections->content, O_TRUNC);
	else
		fd = wrppd_open(msh, redirections->content, O_APPEND);
	wrppd_dup2(msh, fd, STDOUT_FILENO);
	wrppd_close(msh, fd);
}

void	redirect_inpipe(t_msh *msh, t_exec *current)
{
	if (current->prev)
		wrppd_dup2(msh, current->prev->out_pipe[0], STDIN_FILENO);
}

void	redirect_outpipe(t_msh *msh, t_exec *current)
{
	if (current->next)
		wrppd_dup2(msh, current->out_pipe[1], STDOUT_FILENO);
}

void	create_out_pipe(t_msh *msh, t_exec *current)
{
	if (current->next)
	{
		if (pipe(current->out_pipe) == -1)
		{
			close_previous_pipe(msh, current);
			error_simple(msh, "Failed to create pipe", 1);
		}
		current->pipe = true;
	}
}
