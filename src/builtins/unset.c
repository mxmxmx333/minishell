/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:06 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/05 13:03:15 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_node(t_msh *msh, t_env *node)
{
	t_env	*tmp;

	if (msh->env == node)
		msh->env = node->next;
	else
	{
		tmp = msh->env;
		while (tmp && tmp->next != node)
			tmp = tmp->next;
		if (tmp != NULL)
			tmp->next = node->next;
	}
	free(node->v_name);
	free(node->v_value);
	free(node);
}

static void	rem_dest_conv_sort(t_msh *msh, t_env *env)
{
	remove_env_node(msh, env);
	destroy_exp(msh);
	convert_exp(msh);
	sort_export_array(msh);
}

int	command_unset(t_msh *msh, t_exec *exec, int fd)
{
	t_env	*env;
	int		i;

	(void)fd;
	if (!exec->args[1])
		return (0);
	i = 0;
	while (exec->args[++i])
	{
		env = msh->env;
		while (env)
		{
			if (ft_strnrealcmp(env->v_name, exec->args[i],
					ft_strlen(exec->args[i])) == 0)
			{
				rem_dest_conv_sort(msh, env);
				msh->env_size = env_size(msh);
				break ;
			}
			env = env->next;
		}
	}
	return (0);
}
