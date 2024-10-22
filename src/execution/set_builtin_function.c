/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_builtin_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:29:57 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/22 13:31:07 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_builtin_function(t_msh *msh, t_exec *exec)
{
	char	*cmdname;

	(void)msh;
	cmdname = exec->args[0];
	if (ft_strnrealcmp(cmdname, "echo", ft_strlen(cmdname)) == 0)
		exec->builtin = &command_echo;
	if (ft_strnrealcmp(cmdname, "cd", ft_strlen(cmdname)) == 0)
		exec->builtin = &command_cd;
	if (ft_strnrealcmp(cmdname, "pwd", ft_strlen(cmdname)) == 0)
		exec->builtin = &command_pwd;
	if (ft_strnrealcmp(cmdname, "export", ft_strlen(cmdname)) == 0)
		exec->builtin = &command_export;
	//if (ft_strnrealcmp(cmdname, "unset", ft_strlen(cmdname)) == 0)
		//exec->builtin = &command_echo;
	if (ft_strnrealcmp(cmdname, "env", ft_strlen(cmdname)) == 0)
		exec->builtin = &command_env;
	//if (ft_strnrealcmp(cmdname, "exit", ft_strlen(cmdname)) == 0)
	//	exec->builtin = &command_echo;
}
