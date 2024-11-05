/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:31:05 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/05 15:41:18 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dis_exit_err(char *cmdname, char *arg, char *errmsg)
{
	//ft_putstr_fd(RED, STDERR_FILENO);
	//ft_putstr_fd(BOLD, STDERR_FILENO);
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(cmdname, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	//ft_putstr_fd(RESET, STDERR_FILENO
}

static int	check_digits(char *str)
{
	int	i;

	i = -1;
	if (!*str)
		return (0);
	if (str[0] == '+' || str[0] ==  '-')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

static void	error_numeric(t_msh *msh, t_exec *exec)
{
	dis_func_err("exit: ", exec->args[1], "numeric argument required");
	destroy_minishell(msh);
	exit(2);
}

static void	exit_with_code(t_msh *msh, t_exec *exec)
{
	long long	ex_code;

	if (ft_strlen(exec->args[1]) > 19)
		error_numeric(msh, exec);
	ex_code = ft_atoi_custom(exec->args[1]);
	if (ex_code > LLONG_MAX || ex_code < LLONG_MIN)
		error_numeric(msh, exec);
	destroy_minishell(msh);
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
	if (exec->args[1] && !check_digits(exec->args[1]))
		error_numeric(msh, exec);
	while (exec->args[i])
		i++;
	if (i > 2)
		return (dis_exit_err("exit: ", NULL, "too many arguments"), 1);
	if (!exec->args[1])
	{
		destroy_minishell(msh);
		exit(0);
	}
	else
		exit_with_code(msh, exec);
	return (0);
}
