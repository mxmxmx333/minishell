/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_builtin_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:29:57 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/12 13:47:33 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_builtin_function(t_exec *exec)
{
	char	*cmdname;

	if (!exec->args || !exec->args[0])
		return ;
	cmdname = exec->args[0];
	if (ft_strnrealcmp(cmdname, "echo", ft_strlen("echo")) == 0)
		exec->builtin = &command_echo;
	if (ft_strnrealcmp(cmdname, "cd", ft_strlen("cd")) == 0)
		exec->builtin = &command_cd;
	if (ft_strnrealcmp(cmdname, "pwd", ft_strlen("pwd")) == 0)
		exec->builtin = &command_pwd;
	if (ft_strnrealcmp(cmdname, "export", ft_strlen("export")) == 0)
		exec->builtin = &command_export;
	if (ft_strnrealcmp(cmdname, "unset", ft_strlen("unset")) == 0)
		exec->builtin = &command_unset;
	if (ft_strnrealcmp(cmdname, "env", ft_strlen("env")) == 0)
		exec->builtin = &command_env;
	if (ft_strnrealcmp(cmdname, "exit", ft_strlen("exit")) == 0)
		exec->builtin = &command_exit;
}

void	set_all_builtins(t_exec *exec)
{
	while (exec)
	{
		set_builtin_function(exec);
		exec = exec->next;
	}
}
