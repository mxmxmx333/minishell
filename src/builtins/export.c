/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:59:52 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/23 15:36:22 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_array(t_msh *msh, int fd)
{
	int	i;

	i = -1;
	if (!msh->export)
	{
		convert_exp(msh);
		sort_export_array(msh);
	}
	while (msh->export[++i])
	{
		if (msh->export[i][0] == '_')
			continue ;
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(msh->export[i], fd);
		ft_putstr_fd("\n", fd);
	}
}

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

/*
	In the case where an existing variable name was not found, just
	create a new node with v_name and v_value.
*/
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

/*
	Allocate memory and copy from args to v_name and v_value.
*/
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
	*v_name = ft_strndup(arg, i);
	if (!ft_strchr(arg, '='))
		*v_value = NULL;
	else
	{
		*v_value = ft_strdup(arg + i + 1);
		if (!v_value)
			return (free(*v_name), -1);
	}
	return (0);
}

int	command_export(t_msh *msh, t_exec *exec, int fd)
{
	int		i;
	char	*v_name;
	char	*v_value;

	i = 0;
	if (!exec->args[1])
		print_export_array(msh, fd);
	while (exec->args[++i])
	{
		allocate_and_copy(msh, exec->args[i], &v_name, &v_value);
		if (search_and_replace(msh, v_name, v_value) == 1)
		{
			free(v_name);
			continue ;
		}
		else
		{
			add_node_env(msh, v_name, v_value);
			destroy_exp(msh);
		}
	}
	msh->env_size = env_size(msh);
	return (0);
}
