/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:27:56 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/18 16:20:06 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_simple(t_msh *msh, char *msg, int exit_code)

{
	ft_putstr_fd(msg, STDERR_FILENO);
	clean_up_minishell(msh);
	exit(exit_code);
}
