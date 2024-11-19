/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:02:12 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/19 11:07:59 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dis_export_err(char *cmdname, char *arg, char *errmsg)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(cmdname, STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	find_v_value(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i == (int)ft_strlen(arg))
		return (0);
	return (i);
}

int	args_numb(char **args)
{
	int	i;

	if (!args || !*args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

static void	format_line(int fd, char *str)
{
	int	j;

	j = 0;
	ft_putstr_fd("declare -x ", fd);
	while (str[j] && str[j] != '=')
		ft_putchar_fd(str[j++], fd);
	if (!str[j])
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	ft_putchar_fd(str[j++], fd);
	ft_putchar_fd('"', fd);
	while (str[j])
		ft_putchar_fd(str[j++], fd);
	ft_putchar_fd('"', fd);
	ft_putstr_fd("\n", fd);
}

void	print_export_array(t_msh *msh, int fd)
{
	int	i;

	i = -1;
	if (!msh->export)
		convert_exp(msh);
	sort_export_array(msh);
	while (msh->export[++i])
	{
		if (msh->export[i][0] == '_' && msh->export[i][1] == '=')
			continue ;
		format_line(fd, msh->export[i]);
	}
}
