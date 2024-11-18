/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:48:34 by mbonengl          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/13 14:24:51 by nicvrlja         ###   ########.fr       */
=======
/*   Updated: 2024/11/18 09:20:56 by mbonengl         ###   ########.fr       */
>>>>>>> dev_ma
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wrpped_close_builtin(t_msh *msh, int fd)
{
	if (fd > 2)
	{
		if (close(fd) == -1)
		{
			dis_func_err(msh, "", FD_ERR, "");
			msh->status = 1;
		}
	}
}

int	wrppd_open(t_msh *msh, char *path, int flags)
{
	int	fd;

	if (flags == O_RDONLY)
		fd = open(path, O_RDONLY);
	else if (flags == O_APPEND)
		fd = open(path, O_APPEND | O_WRONLY | O_CREAT, 0644);
	else
		fd = open(path, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		open_error(msh, errno, path);
	return (fd);
}

int	wrppd_open_builtin(t_msh *msh, char *path, int flags)
{
	int	fd;

	if (flags == O_RDONLY)
		fd = open(path, O_RDONLY);
	else if (flags == O_APPEND)
		fd = open(path, O_APPEND | O_WRONLY | O_CREAT, 0644);
	else
		fd = open(path, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		open_error_builtin(msh, errno, path);
	return (fd);
}
