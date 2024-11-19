/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:16 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/19 11:29:57 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wrapper_dup2(t_msh *msh, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		error_simple(msh, "Failed to duplicate file descriptor", 1);
}

int	wrapper_dup(t_msh *msh)
{
	int	new_fd;

	new_fd = dup(STDIN_FILENO);
	if (!new_fd)
		error_simple(msh, "Failed to duplicate file descriptor", 1);
	return (new_fd);
}
