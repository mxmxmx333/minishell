/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:56:00 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/05 17:26:21 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_exec *exec)
{
	int	i;
	int	j;

	i = 1;
	while (exec->args[i] && exec->args[i][0] == '-')
	{
		j = 1;
		while (exec->args[i][j])
		{
			if (exec->args[i][j] == 'n')
				j++;
			else
				return (i);
		}
		i++;
	}
	return (i);
}

static int	argument_len(t_exec *exec)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (exec->args[++i])
		len += ft_strlen(exec->args[i]);
	len += i;
	return (len);
}

static char	*argument_join__no_newline(t_msh *msh, t_exec *exec)
{
	char	*str;
	int		i;
	int		j;
	int		p;

	i = count_args(exec) - 1;
	j = 0;
	p = 0;
	str = malloc(argument_len(exec) + 1);
	if (!str)
		return (error_simple(msh, M_ERR, 1), NULL);
	while (exec->args[++i])
	{
		j = 0;
		while (exec->args[i][j])
			str[p++] = exec->args[i][j++];
		if (exec->args[i + 1] != NULL)
			str[p++] = ' ';
	}
	str[p] = '\0';
	return (str);
}

static char	*argument_join_newline(t_msh *msh, t_exec *exec)
{
	char	*str;
	int		i;
	int		j;
	int		p;

	i = 0;
	j = 0;
	p = 0;
	str = malloc(argument_len(exec) + 1 + 1);
	if (!str)
		return (error_simple(msh, M_ERR, 1), NULL);
	while (exec->args[++i])
	{
		j = 0;
		while (exec->args[i][j])
			str[p++] = exec->args[i][j++];
		if (exec->args[i + 1] != NULL)
			str[p++] = ' ';
	}
	str[p++] = '\n';
	str[p] = '\0';
	return (str);
}

int	command_echo(t_msh *msh, t_exec *exec, int fd)
{
	char	*args;

	if (exec->args[1] && check_newline(exec))
		args = argument_join__no_newline(msh, exec);
	else
		args = argument_join_newline(msh, exec);
	ft_putstr_fd(args, fd);
	free(args);
	return (0);
}
