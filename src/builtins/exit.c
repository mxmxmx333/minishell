/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:31:05 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/30 16:27:51 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_digits(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

static void	error_numeric(t_msh *msh, t_exec *exec)
{
	destroy_minishell(msh);
	dis_func_err("exit: ", exec->args[1], "numeric argument required");
	exit(2);
}

static void	exit_with_code(t_msh *msh, t_exec *exec)
{
	int	ex_code;

	destroy_minishell(msh);
	ex_code = ft_atoi(exec->args[1]);
	exit(ex_code);
}

int	command_exit(t_msh *msh, t_exec *exec, int fd)
{
	int		i;

	(void)fd;
	i = 1;
	if (exec->next)
		return (0);
	printf("exit\n");
	while (exec->args[i])
		i++;
	if (i > 2)
		return (dis_func_err("exit: ", NULL, "too many arguments\n"), 1);
	if (!exec->args[1])
	{
		destroy_minishell(msh);
		exit(0);
	}
	if (check_digits(exec->args[1]))
		exit_with_code(msh, exec);
	else
		error_numeric(msh, exec);
	return (0);
}
