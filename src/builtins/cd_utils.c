/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:09:51 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/14 15:04:06 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_variable_finder(t_msh *msh, char *node)
{
	t_env	*tmp;

	tmp = msh->env;
	while (tmp)
	{
		if (!ft_strnrealcmp(tmp->v_name, node, ft_strlen(node)))
			return (tmp->v_value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*env_node_finder(t_msh *msh, char *node)
{
	t_env	*tmp;

	tmp = msh->env;
	while (tmp)
	{
		if (!ft_strnrealcmp(tmp->v_name, node, ft_strlen(node)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	change_directory(t_msh *msh, char *dir)
{
	if (chdir(dir))
		return (cd_errors(msh, errno, dir), 0);
	return (1);
}

void	create_oldpwd_node(t_msh *msh, char *oldpwd)
{
	char	*tmp_val;
	char	*tmp_name;

	tmp_val = ft_strdup(oldpwd);
	if (!tmp_val)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	tmp_name = ft_strdup("OLDPWD");
	if (!tmp_val)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	add_node_env(msh, tmp_name, tmp_val);
}

void	create_pwd_node(t_msh *msh, char *pwd)
{
	char	*tmp_val;
	char	*tmp_name;

	tmp_val = ft_strdup(pwd);
	if (!tmp_val)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	tmp_name = ft_strdup("PWD");
	if (!tmp_val)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	add_node_env(msh, tmp_name, tmp_val);
}
