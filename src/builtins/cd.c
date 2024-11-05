/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:14:57 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/05 19:30:01 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_errors(int errcode, char *arg)
{
	if (errcode == ENOTDIR)
		dis_func_err("cd: ", arg, "Not a directory");
	else if (errcode == ENOENT)
		dis_func_err("cd: ", arg, "No such file or directory");
	else if (errcode == EACCES)
		dis_func_err("cd: ", arg, "Permission denied");
	else if (errcode == EFAULT)
		dis_func_err("cd: ", arg, "Bad address");
	else if (errcode == EIO)
		dis_func_err("cd: ", arg, "Input/output error");
	else if (errcode == ELOOP)
		dis_func_err("cd: ", arg, "Too many simbolic links");
	else if (errcode == ENAMETOOLONG)
		dis_func_err("cd: ", arg, "Name too long");
	else if (errcode == EROFS)
		dis_func_err("cd: ", arg, "Read-only file system");
	else if (errcode == ENOMEM)
		dis_func_err("cd: ", arg, "Out of memory");
}

static void	update_env(t_msh *msh, char *pwd, char *oldpwd)
{
	t_env	*temp;

	temp = msh->env;
	while (temp)
	{
		if (ft_strnrealcmp(temp->v_name, "PWD", ft_strlen("PWD")) == 0)
		{
			if (temp->v_value)
				free(temp->v_value);
			temp->v_value = ft_strdup(pwd);
			if (!temp->v_value)
				error_simple(msh, M_ERR, EXIT_FAILURE);
		}
		if (ft_strnrealcmp(temp->v_name, "OLDPWD", ft_strlen("OLDPWD")) == 0)
		{
			if (temp->v_value)
				free(temp->v_value);
			temp->v_value = ft_strdup(oldpwd);
			if (!temp->v_value)
				error_simple(msh, M_ERR, EXIT_FAILURE);
		}
		temp = temp->next;
	}
}
static void	free_stuff(t_msh *msh, char *oldpwd)
{
	char	*newpwd;
	
	newpwd = getcwd(NULL, 0);
	update_env(msh, newpwd, oldpwd);
	free(oldpwd);
	free(newpwd);
	free(msh->cur_dir);
	free(msh->prompt);
	create_prompt(msh);
}

int	previous_dir(t_msh *msh, char *oldpwd)
{
	char	*newpwd;

	newpwd = ft_strdup(env_variable_finder(msh, "OLDPWD"));
	if(chdir(newpwd) == -1)
		return(cd_errors(errno, newpwd), free(newpwd), 1);
	update_env(msh, newpwd, oldpwd);
	printf("%s\n", newpwd);
	free(oldpwd);
	free(newpwd);
	free(msh->cur_dir);
	free(msh->prompt);
	create_prompt(msh);
	return (0);
}

int	command_cd(t_msh *msh, t_exec *exec, int fd)
{
	char	*oldpwd;
	int		i;

	(void)fd;
	i = 0;
	while (exec->args[i])
		i++;
	if (i > 2)
		return(dis_func_err("cd", "", "too many arguments"), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd error"), -1);
	if (!exec->args[1])
	{
		if (chdir(msh->home_dir) == -1)
			return (free(oldpwd), cd_errors(errno, msh->home_dir), 1);
		return (free(msh->cur_dir), free(msh->prompt), create_prompt(msh),
			update_env(msh, msh->home_dir, oldpwd), free(oldpwd), 0);
	}
	if (ft_strlen(exec->args[1]) == 1 && exec->args[1][0] == '-')
			return (previous_dir(msh, oldpwd));
	if (chdir(exec->args[1]) == -1)
		return (free(oldpwd), cd_errors(errno, exec->args[1]), 1);
	free_stuff(msh, oldpwd);
	return (0);
}
