/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:48:34 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/22 18:04:36 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_error(t_msh *msh, int errorcode, char *path)
{
	if (errorcode == EACCES)
		error_complex(msh, path, O_PER_ERR, 1);
	else if (errorcode == EEXIST)
		error_complex(msh, path, ": file exists", 1);
	else if (errorcode == EISDIR)
		error_complex(msh, path, ": is a directory", 1);
	else if (errorcode == ENOMEM)
		error_simple(msh, M_ERR, 1);
	else if (errorcode == EROFS)
		error_complex(msh, path, ": read-only file system", 1);
	else if (errorcode == ELOOP)
		error_complex(msh, path, ": too many levels of symbolic links", 1);
	else if (errorcode == ENAMETOOLONG)
		error_complex(msh, path, ": file name too long", 1);
	else if (errorcode == EMFILE)
		error_complex(msh, path, ": too many open files", 1);
	else if (errorcode == 	EFAULT)
		error_complex(msh, path, ": bad address", 1);
	else if (errorcode == EINTR)
		error_complex(msh, path, ": interrupted function call", 1);
	else if (errorcode == ENOSPC)
		error_complex(msh, path, ": no space left on device", 1);
	else
		error_complex(msh, path, ": no such file or directory", 1);
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
