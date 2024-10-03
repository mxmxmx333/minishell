/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:42:01 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/03 17:38:48 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Function to free the prompt.
*/
void	destroy_prompt(t_msh *msh)
{
	if (msh)
	{
		if (msh->prompt)
		{
			free(msh->prompt);
			msh->prompt = NULL;
		}
		if (msh->hostname)
		{
			free(msh->hostname);
			msh->hostname = NULL;
		}
	}
}

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
	this function will destroy the current command line
*/
void	destroy_cmd_line(t_msh *msh)
{
	if (msh->cur_cmd_line)
	{
		free(msh->cur_cmd_line);
		msh->cur_cmd_line = NULL;
	}
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
		destroy_tokens(msh);
		destroy_cmd_line(msh);
		destroy_prompt(msh);
		ft_free((void **)&msh);
	}
}
