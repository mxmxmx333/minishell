/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:48:25 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/17 11:27:07 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This file contains is the header file for the minishell project, which con- 
**	tains the part of the minishell, that is responsible for the main execution 
**	of the program.
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries.h"

/*-----------------------------> Initialization <-----------------------------*/

t_msh	*initialize_minishell(char **env);
void	exit_success(t_msh *msh);

/*-----------------------------> Implementation <-----------------------------*/

void	minishell_interface(t_msh *msh);
int		lexer(t_msh *msh);

#endif
