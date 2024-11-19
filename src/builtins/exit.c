/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:31:05 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/18 18:16:29 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dis_exit_err(t_msh *msh, char *cmdname, char *arg, char *errmsg)
{
	char	*err_msg;
	char	*tmp;

	err_msg = ft_strjoin_three("msh: ", cmdname, arg);
	if (!err_msg)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	tmp = err_msg;
	err_msg = ft_strjoin_three(err_msg, errmsg, "\n");
	free(tmp);
	if (!err_msg)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	free(err_msg);
}

static int	check_digits(char *str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (str[i] == ' ' && str[i + 1] != '\0' && str[i + 1] != ' ')
				return (0);
			else if (str[i] == ' ')
			{
				i++;
				continue ;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

static void	error_numeric(t_msh *msh, t_exec *exec)
{
	printf("exit\n");
	dis_func_err(msh, "exit: ", exec->args[1], "numeric argument required");
	if (!exec->next && !exec->prev)
	{
		destroy_minishell(msh);
		exit(2);
	}
}

static void	exit_with_code(t_msh *msh, t_exec *exec, int *status)
{
	long long	ex_code;

	ex_code = ft_atoi_custom(exec->args[1]);
	if (ex_code == -300 || ex_code == -301)
	{
		error_numeric(msh, exec);
		*status = 2;
		return ;
	}
	*status = ex_code % 256;
	if (*status < 0)
		*status += 256;
	if (!exec->next && !exec->prev)
	{
		printf("exit\n");
		destroy_minishell(msh);
		exit(ex_code);
	}
}

int	command_exit(t_msh *msh, t_exec *exec, int fd)
{
	int		status;

	(void)fd;
	status = 0;
	if (exec->args[1] && !check_digits(exec->args[1]))
		error_numeric(msh, exec);
	if (args_numb(exec->args) > 2)
	{
		printf("exit\n");
		return (dis_exit_err(msh, "exit: ", "", "too many arguments"), 1);
	}
	if (!exec->args[1])
	{
		if (exec->next || exec->prev)
			return (status);
		printf("exit\n");
		destroy_minishell(msh);
		exit(0);
	}
	else
		exit_with_code(msh, exec, &status);
	return (status);
}
