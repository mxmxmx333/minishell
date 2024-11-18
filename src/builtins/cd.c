/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:14:57 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/14 17:34:01 by nicvrlja         ###   ########.fr       */
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

static int	update_env(t_msh *msh, char *pwd, char *oldpwd)
{
	t_env	*pwd_env;
	t_env	*oldpwd_env;
	char	*tmp_pwd;
	char	*tmp_oldpwd;

	oldpwd_env = env_node_finder(msh, "OLDPWD");
	if (oldpwd_env)
	{
		if (oldpwd_env->v_value)
			free(oldpwd_env->v_value);
		oldpwd_env->v_value = ft_strdup(oldpwd);
		if (!oldpwd_env->v_value)
			error_simple(msh, M_ERR, EXIT_FAILURE);
	}
	else
	{
		tmp_oldpwd = ft_strdup(oldpwd);
		if (!tmp_oldpwd)
			error_simple(msh, M_ERR, EXIT_FAILURE);
		add_node_env(msh, "OLDPWD", tmp_oldpwd);
	}
	pwd_env = env_node_finder(msh, "PWD");
	if (pwd_env)
	{
		if (pwd_env->v_value)
			free(pwd_env->v_value);
		pwd_env->v_value = ft_strdup(pwd);
		if (!pwd_env->v_value)
			error_simple(msh, M_ERR, EXIT_FAILURE);
	}
	else
	{
		tmp_pwd = ft_strdup(pwd);
		if (!tmp_pwd)
			error_simple(msh, M_ERR, EXIT_FAILURE);
		add_node_env(msh, "PWD", tmp_pwd);
	}
	msh->env_size = env_size(msh);
	return (1);
}

static int	free_stuff(t_msh *msh)
{
	char	*newpwd;
	t_env	*env;
	char	*pwd;
	
	pwd = NULL;
	newpwd = getcwd(NULL, 0);
	env = env_node_finder(msh, "PWD");
	if (env)
	{
		pwd = ft_strdup(env->v_value);
		if (!pwd)
			error_simple(msh, M_ERR, EXIT_FAILURE);
		update_env(msh, newpwd, pwd);
		free(pwd);
	}
	else
		update_env(msh, newpwd, "");
	free(newpwd);
	free(msh->cur_dir);
	free(msh->prompt);
	create_prompt(msh);
	return (1);
}

int	previous_dir(t_msh *msh)
{
	char	*newpwd;

	newpwd = ft_strdup(env_variable_finder(msh, "OLDPWD"));
	if(!change_directory(msh, newpwd))
		return(free(newpwd), 0);
	printf("%s\n", newpwd);
	free(newpwd);
	free(msh->cur_dir);
	free(msh->prompt);
	create_prompt(msh);
	return (1);
}

int	command_cd(t_msh *msh, t_exec *exec, int fd)
{
	(void)fd;
	if (exec->next || exec->prev)
		return (0);
	if (args_numb(exec->args) > 2)
		return(dis_func_err(msh, "cd", "", "too many arguments"), 1);
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
	free_stuff(msh);
	return (0);
}
