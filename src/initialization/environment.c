/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:56:42 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/30 10:53:29 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	completely frees one node safely 
*/
void	free_env_node(t_env **node)
{
	if (node && *node)
	{
		if ((*node)->v_name)
			free((*node)->v_name);
		if ((*node)->v_value)
			free((*node)->v_value);
		ft_free((void **)node);
	}
}

/* 
	completely frees the environment list
*/
void	destroy_env(t_msh *msh)
{
	t_env	*tmp;

	while (msh->env)
	{
		tmp = msh->env;
		msh->env = msh->env->next;
		free_env_node(&tmp);
	}
	msh->env = NULL;
}

/* 
**	adds a node to the environment list
*/
void	add_env_node(t_msh *msh, t_env *node)
{
	t_env	*tmp;

	if (!msh->env)
	{
		msh->env = node;
		return ;
	}
	tmp = msh->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

/* 
**	creates a node for the environment list
*/
t_env	*create_env_node(t_msh *msh, char *env)
{
	t_env	*node;
	int		i;

	node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!node)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	node->v_name = ft_strndup(env, i);
	node->v_value = ft_strdup(env + i + 1);
	node->next = NULL;
	if (!node->v_name || !node->v_value)
		return (free_env_node(&node),
			error_simple(msh, M_ERR, EXIT_FAILURE), NULL);
	return (node);
}

/* 
**	initializes the environment list 
*/
void	initialize_environment(t_msh *msh, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		add_env_node(msh, create_env_node(msh, env[i]));
	msh->env_size = i;
}
