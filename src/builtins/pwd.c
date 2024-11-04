/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:53:50 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/31 15:40:09 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_pwd(t_msh *msh, t_exec *exec, int fd)
{
	(void)exec;
	ft_putstr_fd(msh->cur_dir, fd);
	ft_putstr_fd("\n", fd);
	return (0);
}
