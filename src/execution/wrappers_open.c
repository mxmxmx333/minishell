/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:48:34 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/05 14:22:26 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_error(t_msh *msh, int errorcode, char *path)
{
	if (errorcode == EACCES)
		error_complex(msh, O_PER_ERR, path, 1);
	else if (errorcode == EEXIST)
		error_complex(msh, ": file exists", path, 1);
	else if (errorcode == EISDIR)
		error_complex(msh, ": is a directory", path, 1);
	else if (errorcode == ENOMEM)
		error_simple(msh, M_ERR, 1);
	else if (errorcode == EROFS)
		error_complex(msh, ": read-only file system", path, 1);
	else if (errorcode == ELOOP)
		error_complex(msh, ": too many levels of symbolic links", path, 1);
	else if (errorcode == ENAMETOOLONG)
		error_complex(msh, ": file name too long", path, 1);
	else if (errorcode == EMFILE)
		error_complex(msh, ": too many open files", path, 1);
	else if (errorcode == EFAULT)
		error_complex(msh, ": bad address", path, 1);
	else if (errorcode == EINTR)
		error_complex(msh, ": interrupted function call", path, 1);
	else if (errorcode == ENOSPC)
		error_complex(msh, ": no space left on device", path, 1);
	else
		error_complex(msh, ": no such file or directory", path, 1);
}

static void	open_error_builtin(t_msh *msh, int errorcode, char *path)
{
	if (errorcode == EACCES)
		dis_func_err("", path, O_PER_ERR);
	else if (errorcode == EEXIST)
		dis_func_err("", path, ": file exists");
	else if (errorcode == EISDIR)
		dis_func_err("", path, ": is a directory");
	else if (errorcode == ENOMEM)
		error_simple(msh, M_ERR, 1);
	else if (errorcode == EROFS)
		dis_func_err("", path, ": read-only file system");
	else if (errorcode == ELOOP)
		dis_func_err("", path, ": too many levels of symbolic links");
	else if (errorcode == ENAMETOOLONG)
		dis_func_err("", path, ": file name too long");
	else if (errorcode == EMFILE)
		dis_func_err("", path, ": too many open files");
	else if (errorcode == EFAULT)
		dis_func_err("", path, ": bad address");
	else if (errorcode == EINTR)
		dis_func_err("", path, ": interrupted function call");
	else if (errorcode == ENOSPC)
		dis_func_err("", path, ": no space left on device");
	else
		dis_func_err("", path, ": no such file or directory");
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