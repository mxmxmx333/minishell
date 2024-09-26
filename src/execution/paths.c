/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:55:37 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 18:55:43 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* destroys the paths safely*/
void	destroy_paths(t_msh *msh)
{
	if (msh->paths)
		destroy_str_array(msh->paths);
	msh->paths = NULL;
}

/* extracts the path from the environment list */
void	extract_paths(t_msh *msh)
{
	t_env	*tmp;
	char	**paths;

	tmp = msh->env;
	while (strncmp(tmp->v_name, "PATH", 4))
		tmp = tmp->next;
	paths = ft_split(tmp->v_value, ':');
	if (!paths)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	if (msh->paths)
		destroy_paths(msh);
	msh->paths = paths;
}
