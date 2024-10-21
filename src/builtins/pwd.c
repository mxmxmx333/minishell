/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:43:33 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/21 17:49:25 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_pwd(t_msh *msh, t_exec *exec)
{
	(void)exec;
	printf("%s\n", msh->cur_dir);
	return (0);
}
