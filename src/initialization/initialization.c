/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:56:36 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/01 16:47:08 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function initializes the minishell strucure, as well as the necessary
**	additional structures to run the minishell program.
*/
t_msh	*initialize_minishell(char **env)
{
	t_msh	*msh;

	msh = (t_msh *)ft_calloc(sizeof(t_msh), 1);
	if (!msh)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	initialize_environment(msh, env);
	msh->hostname = get_hostname();
	msh->username = getenv("USER");
	msh->home_dir = getenv("HOME");
	if (create_prompt(msh))
		error_simple(msh, PR_ERR, 1);
	return (msh);
}
