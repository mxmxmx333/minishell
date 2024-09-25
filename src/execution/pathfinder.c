/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:55:35 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/25 16:43:08 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_exe_path(t_msh *msh)
{
	if (msh->exe_path)
	{
		free(msh->exe_path);
		msh->exe_path = NULL;
	}
}

/*
	If a '/' is found in the string, the command ins going to be interpreted 
	as a absolute or relative path.
*/
static int	is_real_path(char *path)
{
	if (ft_strchr(path, '/'))
		return (1);
	return (0);
}

/*
	This function is going to check, if path is executable, if not 
	it will check for dir, and file agnd return the appropriate error message.
*/
static int	check_relabs_path(t_msh *msh, char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (error_complex(msh, DIR_ERR, path, 126), 0);
	}
	if (access(path, X_OK) == 0)
	{
		msh->exe_path = ft_strdup(path);
		return (1);
	}
	if (access(path, F_OK) == 0)
		return (error_complex(msh, PER_ERR, path, 126), 0);
	return (error_complex(msh, NODF_ERR, path, 127), 0);
}

static void	check_f_ok(t_msh *msh, char *path)
{
	int		i;
	char	*tmp_path;

	i = -1;
	while (msh->paths[++i])
	{
		tmp_path = ft_strjoin_three(msh->paths[i], "/", path);
		if (access(tmp_path, F_OK) == 0)
			return (free(tmp_path), error_complex(msh, PER_ERR, path, 126));
		free(tmp_path);
	}
}

/* 
	Will set the "msh->exe_path" to the path of the executable, and do the 
	error handling for the cmd execution
	pathfinder will segfault, when one of the inputs is NULL
*/
int	pathfinder(t_msh *msh, char *path)
{
	char	*tmp_path;
	int		i;

	if (!path || !msh)
		return (error_simple(msh, PATHFINDER_ERR, 1), 1);
	if (is_real_path(path))
		return (check_relabs_path(msh, path));
	i = -1;
	if (str_is_empty(path))
		return (error_complex(msh, CMDNF_ERR, path, 127), 0);
	while (msh->paths[++i])
	{
		tmp_path = ft_strjoin_three(msh->paths[i], "/", path);
		if (!tmp_path)
			return (error_simple(msh, M_ERR, 1), 0);
		if (access(tmp_path, X_OK) == 0)
		{
			msh->exe_path = tmp_path;
			return (1);
		}
		free(tmp_path);
	}
	check_f_ok(msh, path);
	return (error_complex(msh, CMDNF_ERR, path, 127), 0);
}
