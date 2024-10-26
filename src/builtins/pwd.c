/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:53:50 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/24 14:54:55 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_pwd(t_msh *msh, t_exec *exec, int fd)
{
	(void)exec;
	ft_putstr_fd(msh->cur_dir, fd);
	return (0);
}
