/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:11:55 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/18 17:12:58 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	destroys the export safely
*/
void	destroy_exp(t_msh *msh)
{
	if (msh->export)
		destroy_str_array(msh->export);
	msh->export = NULL;
}

static char	**allocate_memory(t_msh *msh, t_env **tmp)
{
	char	**env;

	env = (char **)ft_calloc(msh->env_size + 1, sizeof(char *));
	if (!env)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	if (msh->export)
		destroy_exp(msh);
	*tmp = msh->env;
	return (env);
}

void	write_one_node(t_msh *msh, t_env *current, int i, char **env)
{
	int		shlvl;
	char	*lvl;

	if (!strcmp(current->v_name, "SHLVL"))
	{
		shlvl = ft_atoi(current->v_value) + 1;
		lvl = ft_itoa(shlvl);
		if (!lvl)
			error_simple(msh, M_ERR, EXIT_FAILURE);
		env[i] = ft_strjoin_three(current->v_name, "=", lvl);
		free(lvl);
		if (!env[i])
			return (free(lvl), error_simple(msh, M_ERR, EXIT_FAILURE));
		return ;
	}
	if (!current->v_value)
	{
		env[i] = ft_strdup(current->v_name);
		if (!env[i])
			error_simple(msh, M_ERR, EXIT_FAILURE);
		return ;
	}
	env[i] = ft_strjoin_three(current->v_name, "=", current->v_value);
	if (!env[i])
		error_simple(msh, M_ERR, EXIT_FAILURE);
}

/*	
	converts the environment list for export environment
*/
void	convert_exp(t_msh *msh)
{
	char	**env;
	t_env	*tmp;
	int		i;

	env = allocate_memory(msh, &tmp);
	msh->export = env;
	i = 0;
	while (tmp)
	{
		write_one_node(msh, tmp, i, env);
		tmp = tmp->next;
		i++;
	}
	msh->export = env;
}
