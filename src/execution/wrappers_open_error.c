/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_open_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:19:15 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/18 09:27:41 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dis_func_err_open(char *cmdname, char *arg, char *errmsg)
{
	//ft_putstr_fd(RED, STDERR_FILENO);
	//ft_putstr_fd(BOLD, STDERR_FILENO);
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(cmdname, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	//ft_putstr_fd(RESET, STDERR_FILENO);
}

void	open_error(t_msh *msh, int errorcode, char *path)
{
	if (errorcode == EACCES)
		error_complex(msh, O_PER_ERR, path, 1);
	else if (errorcode == EEXIST)
		error_complex(msh, ": File exists", path, 1);
	else if (errorcode == EISDIR)
		error_complex(msh, ": Is a directory", path, 1);
	else if (errorcode == ENOMEM)
		error_simple(msh, M_ERR, 1);
	else if (errorcode == EROFS)
		error_complex(msh, ": Read-only file system", path, 1);
	else if (errorcode == ELOOP)
		error_complex(msh, ": Too many levels of symbolic links", path, 1);
	else if (errorcode == ENAMETOOLONG)
		error_complex(msh, ": File name too long", path, 1);
	else if (errorcode == EMFILE)
		error_complex(msh, ": Too many open files", path, 1);
	else if (errorcode == EFAULT)
		error_complex(msh, ": Bad address", path, 1);
	else if (errorcode == EINTR)
		error_complex(msh, ": Interrupted function call", path, 1);
	else if (errorcode == ENOSPC)
		error_complex(msh, ": No space left on device", path, 1);
	else
		error_complex(msh, ": No such file or directory", path, 1);
}

void	open_error_builtin(t_msh *msh, int errorcode, char *path)
{
	msh->status = 1;
	if (errorcode == EACCES)
		dis_func_err_open("", path, O_PER_ERR);
	else if (errorcode == EEXIST)
		dis_func_err_open("", path, ": File exists");
	else if (errorcode == EISDIR)
		dis_func_err_open("", path, ": Is a directory");
	else if (errorcode == ENOMEM)
		error_simple(msh, M_ERR, 1);
	else if (errorcode == EROFS)
		dis_func_err_open("", path, ": Read-only file system");
	else if (errorcode == ELOOP)
		dis_func_err_open("", path, ": Too many levels of symbolic links");
	else if (errorcode == ENAMETOOLONG)
		dis_func_err_open("", path, ": File name too long");
	else if (errorcode == EMFILE)
		dis_func_err_open("", path, ": Too many open files");
	else if (errorcode == EFAULT)
		dis_func_err_open("", path, ": bad address");
	else if (errorcode == EINTR)
		dis_func_err_open("", path, ": Interrupted function call");
	else if (errorcode == ENOSPC)
		dis_func_err_open("", path, ": No space left on device");
	else
		dis_func_err_open(path, "", ": No such file or directory");
}
