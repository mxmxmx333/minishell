/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:56:36 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/21 14:30:17 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_status(int *msh_status)
{
	static int	*stat = NULL;

	if (msh_status)
		stat = msh_status;
	return (stat);
}

/*
	This function initializes the minishell strucure, as well as the necessary
	additional structures to run the minishell program.
*/
t_msh	*initialize_minishell(char **env)
{
	t_msh	*msh;

	msh = (t_msh *)ft_calloc(sizeof(t_msh), 1);
	if (!msh)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	initialize_environment(msh, env);
	msh->hostname = get_hostname();
	if (!msh->hostname)
		error_simple(msh, PR_ERR, 1);
	msh->username = getenv("USER");
	if (!msh->username)
		error_simple(msh, PR_ERR, 1);
	msh->home_dir = getenv("HOME");
	if (!msh->home_dir)
		error_simple(msh, PR_ERR, 1);
	if (create_prompt(msh))
		error_simple(msh, PR_ERR, 1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	load_history(msh, ".msh_history.txt");
	get_status(&msh->status);
	return (msh);
}
