/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:27:56 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/18 18:25:25 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_simple(t_msh *msh, char *msg, int exit_code)

{
	ft_putstr_fd(msg, STDERR_FILENO);
	destroy_minishell(msh);
	exit(exit_code);
}
