/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:53:04 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/18 17:02:06 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_env(t_msh *msh, t_exec *exec, int fd)
{
	t_env	*temp;

	(void)exec;
	temp = msh->env;
	while (temp)
	{
		if (!temp->v_value)
		{
			temp = temp->next;
			continue ;
		}
		ft_putstr_fd(temp->v_name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(temp->v_value, fd);
		ft_putstr_fd("\n", fd);
		temp = temp->next;
	}
	return (0);
}
