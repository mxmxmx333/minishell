/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:42:01 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/19 12:40:45 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	
	destroys an array of strings safely, by freeing each string, then the array
*/
void	destroy_str_array(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		free(str[i]);
	free(str);
}

/* 	
	this function calls all the other destroy functions, and frees minishell, 
	to prepare a safe exit
*/
void	destroy_minishell(t_msh *msh)
{
	if (msh)
	{
		destroy_env(msh);
		destroy_exp(msh);
		destroy_paths(msh);
		destroy_exe_path(msh);
		ft_free((void **)&msh);
	}
}
