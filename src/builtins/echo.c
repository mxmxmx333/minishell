/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:56:00 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/21 14:20:47 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	argument_len(t_exec *exec)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (exec->args[++i])
		len += ft_strlen(exec->args[i]);
	len += i;
	return (len);
}

char	*argument_join(t_msh *msh, t_exec *exec)
{
	char	*str;
	int		i;
	int		j;
	int		p;

	i = -1;
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
	return (str);
}

int	echo(t_msh *msh, t_exec *exec)
{
	char	*args;

	args = argument_join(msh, exec);
	if (exec->next)
		ft_putstr_fd(args, exec->out_pipe[1]);
	printf("%s", args);
	if (strcmp(exec->args[1], "-n") != 0)
		printf("\n");
	return (0);
}
