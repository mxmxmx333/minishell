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

int	is_path(char *path)
{
	if (ft_strchr(path, '/'))
		return (1);
	return (0);
}

/*
	Ich muss schauen, ob es einen Weg gibt herauszufinden, nach dem Exec check, ob der Pfad ein directory ist. Ansonsten Error no such file or directory.
*/
int	check_relabs_path(t_msh *msh, char *path)
{
	if (access(path, X_OK) == 0)
	{
		msh->exe_path = ft_strdup(path);
		return (1);
	}
	if (access(path, F_OK) == 0)
		return (error_complex(msh, ));
		
}
