/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:16:58 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/22 17:54:39 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_msh *msh, int fd[2])
{
	if (close(fd[1]) == -1)
		error_simple(msh, "Failed to close pipe", 1);
	if (close(fd[0]) == -1)
		error_simple(msh, "Failed to close pipe", 1);
}

void	close_previous_pipe(t_msh *msh, t_exec *current)
{
	if (current->prev && current->prev->pipe == true)
		close_pipe(msh, current->prev->out_pipe);
	current->prev->pipe = false;
}

void	close_both_pipes(t_msh *msh, t_exec *current)
{
	if (current->prev && current->prev->pipe == true)
		close_pipe(msh, current->prev->out_pipe);
	current->prev->pipe = false;
	if (current->next && current->pipe == true)
		close_pipe(msh, current->out_pipe);
	current->pipe = false;
}
