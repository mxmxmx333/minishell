/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:36:26 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/05 16:43:24 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_newline(t_exec *exec)
{
	int	i;

	i = 1;
	if (exec->args[1][0] != '-')
		return (0);
	if (exec->args[1][0] == '-' && exec->args[1][1] != 'n')
		return (0);
	while (exec->args[1][i])
	{
		if (exec->args[1][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}