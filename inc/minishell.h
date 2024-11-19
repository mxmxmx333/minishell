/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:48:25 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/19 10:52:07 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This file contains is the header file for the minishell project, which con- 
**	tains the part of the minishell, that is responsible for the main execution 
**	of the program.
*/

#ifndef MINISHELL_H
# define MINISHELL_H
# define DISABLE_HISTORY 1
# include "libraries.h"

extern sig_atomic_t g_sig;

/*-----------------------------> Initialization <-----------------------------*/

t_msh	*initialize_minishell(char **env);
void	exit_success(t_msh *msh);

/*-----------------------------> Implementation <-----------------------------*/

void	minishell_interface(t_msh *msh);
int		lexer(t_msh *msh);
int		execution(t_msh *msh);

#endif
