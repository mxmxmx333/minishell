/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:31:05 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/23 15:40:24 by nicvrlja         ###   ########.fr       */
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

int	command_exit(t_msh *msh, t_exec *exec, int fd)
{
	int		i;
	int		ex_code;

	(void)fd;
	i = 1;
	printf("exit\n");
	while (exec->args[i])
		i++;
	if (i > 2)
		return (display_function_error("exit: ", NULL, "too many arguments\n"), -1);
	if (!exec->args[1])
	{
		destroy_minishell(msh);
		exit(0);
	}
	if (check_digits(exec->args[1]))
	{
		destroy_minishell(msh);
		ex_code = ft_atoi(exec->args[1]);
		exit(ex_code);
	}
	else
	{
		destroy_minishell(msh);
		display_function_error("exit: ", exec->args[1], "numeric argument required");
		exit(2);
	}
	return (0);
}
