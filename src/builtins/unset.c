/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:06 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/24 14:49:40 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_node(t_msh *msh, t_env *node)
{
	t_env	*tmp;

	tmp = msh->env;
	while (tmp->next != node)
		tmp = tmp->next;
	tmp->next = node->next;
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
