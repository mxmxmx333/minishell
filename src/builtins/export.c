/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:59:52 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/22 15:16:47 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Check if there is already a variable with the name,if there is then
	update it.
*/
static int	search_and_replace(t_msh *msh, char *v_name, char *v_value)
{
	t_env	*temp;

	temp = msh->env;
	while (temp)
	{
		if (ft_strnrealcmp(temp->v_name, v_name, ft_strlen(temp->v_name)) == 0)
		{
			free(temp->v_value);
			temp->v_value = v_value;
			return (1);
		}
		temp = temp->next;
	}
	return (-1);
}

static void	add_node_env(t_msh *msh, char *v_name, char *v_value)
{
	t_env	*env;
	t_env	*node;

	env = msh->env;
	while (env->next)
		env = env->next;
	node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!node)
		return ;
	node->v_name = v_name;
	node->v_value = v_value;
	node->next = NULL;
	env->next = node;
}

static int	allocate_and_copy(t_msh *msh, char *arg, char **v_name, char **v_value)
{
	int		i;

	(void)msh;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		i++;
	}
	*v_name = ft_calloc(i + 1, sizeof(char));
	if (!*v_name)
		return (-1);
	i = -1;
	while (arg[++i] != '=')
		(*v_name)[i] = arg[i];
	*v_value = ft_strdup(arg + i + 1);
	if (!v_value)
		return (free(*v_name), -1);
	return (0);
}

int	check_value(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (arg[i] == '=')
			break ;
	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int	command_export(t_msh *msh, t_exec *exec, int fd)
{
	int		i;
	char	*v_name;
	char	*v_value;

	i = 0;
	if (!exec->args[1])
		command_env(msh, exec, fd);
	while (exec->args[++i])
	{
		if (!ft_strchr(exec->args[i], '='))
		{
			v_name = ft_strdup(exec->args[i]);
			v_value = ft_strdup("");
			break ;
		}
		else
			allocate_and_copy(msh, exec->args[i], &v_name, &v_value);
		if (search_and_replace(msh, v_name, v_value) == 1)
			continue ;
		else
			add_node_env(msh, v_name, v_value);		
	}
	if (v_name)
		free(v_name);
	if (v_value)
		free(v_value);
	return (0);
}
