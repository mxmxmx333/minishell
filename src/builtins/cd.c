/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:14:57 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/22 13:43:41 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	cd_errors(int errcode, char *arg)
{
	if (errcode == ENOTDIR)
		display_function_error("cd: ", arg, "Not a directory");
	else if (errcode == ENOENT)
		display_function_error("cd: " , arg, "No such file or directory");
	else if (errcode == EACCES)
		display_function_error("cd: ", arg, "Permission denied");
	else if (errcode == EFAULT)
		display_function_error("cd: ", arg, "Bad address");
	else if (errcode == EIO)
		display_function_error("cd: ", arg, "Input/output error");
	else if (errcode == ELOOP)
		display_function_error("cd: ", arg, "Too many simbolic links");
	else if (errcode == ENAMETOOLONG)
		display_function_error("cd: ", arg, "Name too long");
	else if (errcode == EROFS)
		display_function_error("cd: ", arg, "Read-only file system");
	else if (errcode == ENOMEM)
		display_function_error("cd: ", arg, "Out of memory");
}

static void	update_env(t_msh *msh, char *pwd, char *oldpwd)
{
	t_env	*temp;

	temp = msh->env;
	while (temp)
	{
		if (ft_strnrealcmp(temp->v_name, "PWD", ft_strlen(temp->v_name)) == 0)
		{
			free(temp->v_value);
			temp->v_value = ft_strdup(pwd);
		}
		if (ft_strnrealcmp(temp->v_name, "OLDPWD", ft_strlen(temp->v_name)) == 0)
		{
			free(temp->v_value);
			temp->v_value = ft_strdup(oldpwd);
		}
		temp = temp->next;
	}
}

int	command_cd(t_msh *msh, t_exec *exec, int fd)
{
	char	*oldpwd;
	
	(void)fd;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd error"), -1);
	if (!exec->args[1])
	{
		if (chdir(msh->home_dir) == -1)
			return (perror("chdir"), free(oldpwd), cd_errors(errno, msh->home_dir), -1);
		free(msh->cur_dir);
		free(msh->prompt);
		create_prompt(msh);
		return (update_env(msh, msh->home_dir, oldpwd), free(oldpwd), 1);
	}
	if (chdir(exec->args[1]) == -1)
		return (free(oldpwd), cd_errors(errno, exec->args[1]), -1);
	update_env(msh, exec->args[1], oldpwd);
	free(oldpwd);
	free(msh->cur_dir);
	free(msh->prompt);
	create_prompt(msh);
	return (0);
}
