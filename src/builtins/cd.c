/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:14:57 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/21 17:41:41 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	cd_errors(t_msh *msh, int errcode)
{
	if (errcode == ENOTDIR)
		error_complex(msh, "Not a directory", "cd: ", 1);
	else if (errcode == ENOENT)
		error_complex(msh, "No such file or directory", "cd: ", 1);
	else if (errcode == EACCES)
		error_complex(msh, "Permission denied", "cd: ", 1);
	else if (errcode == EFAULT)
		error_complex(msh, "Bad address", "cd: ", 1);
	else if (errcode == EIO)
		error_complex(msh, "Input/output error", "cd: ", 1);
	else if (errcode == ELOOP)
		error_complex(msh, "Too many simbolic links", "cd: ", 1);
	else if (errcode == ENAMETOOLONG)
		error_complex(msh, "Name too long", "cd: ", 1);
	else if (errcode == EROFS)
		error_complex(msh, "Read-only file system", "cd: ", 1);
	else if (errcode == ENOMEM)
		error_complex(msh, "Out of memory", "cd: ", 1);
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

int	command_cd(t_msh *msh, t_exec *exec)
{
	char	*oldpwd;
	
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd error"), -1);
	if (!exec->args[1])
	{
		if (chdir(msh->home_dir) == -1)
			return (perror("chdir"), free(oldpwd), -1);
		free(msh->cur_dir);
		free(msh->prompt);
		create_prompt(msh);
		return (update_env(msh, msh->home_dir, oldpwd), free(oldpwd), 1);
	}
	if (chdir(exec->args[1]) == -1)
		return (free(oldpwd), cd_errors(msh, errno), -1);
	update_env(msh, exec->args[1], oldpwd);
	free(oldpwd);
	free(msh->cur_dir);
	free(msh->prompt);
	create_prompt(msh);
	return (0);
}
