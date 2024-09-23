/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:55:35 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/19 15:02:12 by mbonengl         ###   ########.fr       */
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
int	is_real_path(char *path)
{
	if (ft_strchr(path, '/'))
		return (1);
	return (0);
}

/*
	This function is going to check, if path is executable, if not 
	it will check for dir, and file agnd return the appropriate error message.
*/
int	check_relabs_path(t_msh *msh, char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (error_complex(msh, "is a directory", path, 126), 0);
	}
	if (access(path, X_OK) == 0)
	{
		msh->exe_path = ft_strdup(path);
		return (1);
	}
	if (access(path, F_OK) == 0)
		return (error_complex(msh, "Permission denied", path, 126), 0);
	return (error_complex(msh, "No such file or directory", path, 127), 0);
}

void	check_f_ok(t_msh *msh, char *path)
{
	int		i;
	char	*tmp_path;

	i = -1;
	while (msh->paths[++i])
	{
		tmp_path = ft_strjoin_three(msh->paths[i], "/", path);
		if (access(msh->paths[i], F_OK) == 0)
			return (error_complex(msh, "Permission denied", path, 126), 0);
		free(tmp_path);
	}
}

int	pathfinder(t_msh *msh, char *path)
{
	char	*tmp_path;
	int		i;

	if (is_real_path(path))
		return (check_relabs_path(msh, path));
	i = -1;
	while (msh->paths[++i])
	{
		tmp_path = ft_strjoin_three(msh->paths[i], "/", path);
		if (!tmp_path)
			return (error(msh, "Malloc failed"), 0);
		if (access(tmp_path, X_OK) == 0)
		{
			msh->exe_path = tmp_path;
			return (1);
		}
		free(tmp_path);
	}
	check_f_ok(msh, path);
	return (error_complex(msh, " :command not found", path, 127), 0);
}

