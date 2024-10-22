/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:43:33 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/22 13:45:57 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_pwd(t_msh *msh, t_exec *exec, int fd)
{
	(void)exec;
	ft_putstr_fd(msh->cur_dir, fd);
	return (0);
}
