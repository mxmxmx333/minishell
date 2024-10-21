/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:14:57 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/21 15:08:41 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	update_env(t_msh *msh, char *pwd, char *oldpwd)
{
	t_env	*temp;

	temp = msh->env;
	while (temp)
	{
		if (ft_strncmp(temp->v_name, "PWD", ft_strlen(temp->v_name)) == 0)
			temp->v_value = pwd;
		else if (ft_strncmp(temp->v_name, "OLDPWD", ft_strlen(temp->v_name) == 0))
			temp->v_value = oldpwd;
		temp = temp->next;
	}
}

int	command_cd(t_msh *msh, t_exec *exec)
{
	char	oldpwd[1024];
	
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		return (perror("getcwd error"), -1);
	if (!exec->args[1])
	{
		if (chdir(msh->home_dir) == -1)
			return (perror("chdir"), -1);
		return (update_env(msh, msh->home_dir, oldpwd), 1);
	}
	if (chdir(exec->args[1]) == -1)
		return (perror("chdir"), -1);
	update_env(msh, exec->args[1], oldpwd);
	free(msh->prompt);
	create_prompt(msh);
	return (0);
}