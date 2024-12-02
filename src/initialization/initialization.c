/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:29:49 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/28 19:06:43 by mbonengl         ###   ########.fr       */
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

static void	create_new_shlvl(t_msh *msh, t_env *last)
{
	t_env	*new;

	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		error_simple(msh, M_ERR, 1);
	new->v_name = ft_strdup("SHLVL");
	if (!new->v_name)
		return (free(new), error_simple(msh, M_ERR, 1));
	new->v_value = ft_strdup("0");
	if (!new->v_value)
		return (free(new->v_name), free(new), error_simple(msh, M_ERR, 1));
	last->next = new;
}

static t_env	*search_shlvl_node(t_msh *msh)
{
	t_env	*tmp;

	tmp = msh->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->v_name, "SHLVL"))
			return (tmp);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	msh->env_size++;
	return (tmp);
}

static void	handle_shlvl(t_msh *msh)
{
	t_env	*tmp;
	t_env	*next;

	tmp = search_shlvl_node(msh);
	if (tmp)
	{
		next = tmp->next;
		if (!ft_strcmp(tmp->v_name, "SHLVL") && !tmp->v_value)
		{
			tmp->v_value = ft_strdup("0");
			if (!tmp->v_value)
				error_simple(msh, M_ERR, 1);
			tmp->next = next;
			return ;
		}
		else if (ft_strcmp(tmp->v_name, "SHLVL"))
			create_new_shlvl(msh, tmp);
	}
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
	signal(SIGQUIT, SIG_IGN);
	load_history(msh, ".msh_history.txt");
	get_status(&msh->status);
	handle_shlvl(msh);
	return (msh);
}
