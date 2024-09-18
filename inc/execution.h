/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:50 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/18 17:54:28 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This file contains is the header file for the exe directory, which contains
**	the part of the minishell, that is responsible for executing the commands
**	that are passed to it.
*/

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/*------------------------------> perparation <------------------------------*/

// exports the environment list to the execution environment
void	convert_exp(t_msh *msh);
// destroys the execution environment
void	destroy_exp(t_msh *msh);

#endif