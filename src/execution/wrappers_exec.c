/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:41:47 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/15 11:22:06 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wrppd_dup2(t_msh *msh, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		error_simple(msh, "Failed to duplicate file descriptor", 1);
}

void	wrppd_close(t_msh *msh, int fd)
{
	if (close(fd) == -1)
		error_simple(msh, "Failed to close file descriptor", 1);
}

void	wrppd_pipe(t_msh *msh, int *fd)
{
	if (pipe(fd) == -1)
		error_simple(msh, "Failed to create pipe", 1);
}

int	wrppd_fork(t_msh *msh)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_simple(msh, "Failed to create child process", 1);
	return (pid);
}
