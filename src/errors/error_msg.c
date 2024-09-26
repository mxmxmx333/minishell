/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:27:56 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 18:40:07 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This function will display an error message on stderr and exit the program
	safeley.

	o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o

	msh: minishell structure to destroy at exit
	msg: error message to display on stderr
	exit_code: code to exit the program with
*/
void	error_simple(t_msh *msh, char *msg, int exit_code)
{
	char	*error_msg;

	error_msg = ft_strjoin("msh: ", msg);
	if (!error_msg)
	{
		ft_putstr_fd("Superfatal Malloc Error\n", STDERR_FILENO);
		destroy_minishell(msh);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	free(error_msg);
	destroy_minishell(msh);
	exit(exit_code);
}

void	error_complex(t_msh *msh, char *msg, char *param, int exit_code)
{
	char	*error_msg;

	error_msg = ft_strjoin_three("msh: ", param, msg);
	if (!error_msg)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free(error_msg);
	destroy_minishell(msh);
	exit(exit_code);
}
