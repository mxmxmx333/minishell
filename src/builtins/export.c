/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:59:52 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/18 15:25:45 by nicvrlja         ###   ########.fr       */
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
		if (ft_strnrealcmp(temp->v_name, v_name, ft_strlen(v_name)) == 0)
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
void	add_node_env(t_msh *msh, char *v_name, char *v_value)
{
	t_env	*env;
	t_env	*node;

	env = msh->env;
	while (env->next)
		env = env->next;
	node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!node)
	{
		free(v_name);
		free(v_value);
		error_simple(msh, M_ERR, EXIT_FAILURE);
	}
	node->v_name = v_name;
	node->v_value = v_value;
	node->next = NULL;
	env->next = node;
}

/*
	Allocate memory and copy from args to v_name and v_value.
*/
static int	alloc_copy(t_msh *msh, char *arg, char **v_name, char **v_value)
{
	int		i;

	i = -1;
	while (arg[++i])
		if (arg[i] == '=')
			break ;
	*v_name = ft_strndup(arg, i);
	if (!*v_name)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	if (!ft_strchr(arg, '='))
		*v_value = NULL;
	else
	{
		*v_value = ft_strdup(arg + i + 1);
		if (!*v_value)
		{
			free(*v_name);
			*v_name = NULL;
			error_simple(msh, M_ERR, EXIT_FAILURE);
		}
	}
	return (1);
}

static int	export_variable(t_msh *msh, char *arg, t_exec *exec, int *error)
{
	char	*str;
	char	*v_name;
	char	*v_value;

	str = ft_strndup(arg, find_v_value(arg));
	if (!str)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	if (!check_valid(str))
	{
		free(str);
		*error = 1;
		return (1);
	}
	if (exec->next || exec->prev)
		return (0);
	alloc_copy(msh, arg, &v_name, &v_value);
	if (search_and_replace(msh, v_name, v_value) == 1)
		free(v_name);
	else
		add_node_env(msh, v_name, v_value);
	return (0);
}

int	command_export(t_msh *msh, t_exec *exec, int fd)
{
	int		i;
	int		error;
	int		status;

	status = 0;
	error = 0;
	i = 0;
	if (!exec->args[1])
		print_export_array(msh, fd);
	while (exec->args[++i])
		status = export_variable(msh, exec->args[i], exec, &error);
	msh->env_size = env_size(msh);
	if (error)
		status = error;
	return (status);
}
