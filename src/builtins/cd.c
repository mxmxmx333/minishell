/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:14:57 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/19 10:59:32 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_errors(t_msh *msh, int errcode, char *arg)
{
	if (errcode == ENOTDIR)
		dis_func_err(msh, "cd: ", arg, "Not a directory");
	else if (errcode == ENOENT)
		dis_func_err(msh, "cd: ", arg, "No such file or directory");
	else if (errcode == EACCES)
		dis_func_err(msh, "cd: ", arg, "Permission denied");
	else if (errcode == EFAULT)
		dis_func_err(msh, "cd: ", arg, "Bad address");
	else if (errcode == EIO)
		dis_func_err(msh, "cd: ", arg, "Input/output error");
	else if (errcode == ELOOP)
		dis_func_err(msh, "cd: ", arg, "Too many simbolic links");
	else if (errcode == ENAMETOOLONG)
		dis_func_err(msh, "cd: ", arg, "Name too long");
	else if (errcode == EROFS)
		dis_func_err(msh, "cd: ", arg, "Read-only file system");
	else if (errcode == ENOMEM)
		dis_func_err(msh, "cd: ", arg, "Out of memory");
}

static int	update_env(t_msh *msh, char *pwd, char *oldpwd, t_env *tmp_node)
{
	if (oldpwd && tmp_node && tmp_node->v_value)
	{
		free(tmp_node->v_value);
		tmp_node->v_value = ft_strdup(oldpwd);
		if (!tmp_node->v_value)
			error_simple(msh, M_ERR, EXIT_FAILURE);
	}
	else if (oldpwd)
		create_oldpwd_node(msh, oldpwd);
	else
		remove_env_node(msh, tmp_node);
	tmp_node = env_node_finder(msh, "PWD");
	if (tmp_node && tmp_node->v_value)
	{
		free(tmp_node->v_value);
		tmp_node->v_value = ft_strdup(pwd);
		if (!tmp_node->v_value)
			error_simple(msh, M_ERR, EXIT_FAILURE);
	}
	else
		create_pwd_node(msh, pwd);
	return (1);
}

static int	update_variables(t_msh *msh)
{
	char	*newpwd;
	t_env	*env;
	char	*pwd;

	pwd = NULL;
	newpwd = getcwd(NULL, 0);
	env = env_node_finder(msh, "PWD");
	if (env && env->v_value)
	{
		pwd = ft_strdup(env->v_value);
		if (!pwd)
			error_simple(msh, M_ERR, EXIT_FAILURE);
		update_env(msh, newpwd, pwd, env_node_finder(msh, "OLDPWD"));
		free(pwd);
	}
	else
		update_env(msh, newpwd, NULL, env_node_finder(msh, "OLDPWD"));
	free(newpwd);
	free(msh->cur_dir);
	free(msh->prompt);
	create_prompt(msh);
	msh->env_size = env_size(msh);
	return (1);
}

int	previous_dir(t_msh *msh)
{
	char	*newpwd;

	newpwd = env_variable_finder(msh, "OLDPWD");
	if (!newpwd)
		return (dis_func_err(msh, "cd", "", "OLDPWD not set"), 0);
	if (!change_directory(msh, newpwd))
		return (1);
	printf("%s\n", newpwd);
	update_variables(msh);
	free(msh->cur_dir);
	free(msh->prompt);
	create_prompt(msh);
	return (0);
}

int	command_cd(t_msh *msh, t_exec *exec, int fd)
{
	(void)fd;
	if (exec->next || exec->prev)
		return (0);
	if (args_numb(exec->args) > 2)
		return (dis_func_err(msh, "cd", "", "too many arguments"), 1);
	if (!exec->args[1])
	{
		if (!change_directory(msh, msh->home_dir))
			return (1);
		return (free(msh->cur_dir), free(msh->prompt), create_prompt(msh), 0);
	}
	if (ft_strlen(exec->args[1]) == 1 && exec->args[1][0] == '-')
		return (previous_dir(msh));
	if (!change_directory(msh, exec->args[1]))
		return (1);
	update_variables(msh);
	return (0);
}
