/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:53:37 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/27 13:57:56 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

/*-----------------------------> ERROR MESSAGES <-----------------------------*/

/* 
	FATAL ERRORS <-----------------------------------------------------
*/

/* Malloc failure */
# define M_ERR "Fatal Error: Insufficient memory!\n"

/* 
	EXECUTION ERRORS <-----------------------------------------------------
*/

/* Permission denied*/
# define PER_ERR ": permission denied\n"
/* Is a directory */
# define DIR_ERR ": is a directory\n"
/* No such file or directory */
# define NODF_ERR ": no such file or directory\n"
/* Command not found*/
# define CMDNF_ERR ": command not found\n"

/* 
	SYNTAX ERRORS <-----------------------------------------------------
*/

/* Syntax Error: Unmached quotes */
# define SYN_QUO_ERR "Syntax Error: Unmatched quotes: "

/* 
	Function specific 
		exit with 42!
	super fatal ERRORS 
*/

/* Error message, if Pathfinder recieves NULL input */
# define SUFA_ERR_PATHFINDER "ERR: Pathfinder failed, you tried to input NULL ... \
idiot\n"

/* Error message, if Pathfinder recieves NULL input */
# define SUFA_ERR_SYX_Q_ERR "ERR: You tried to check syntax (quotes) of NULL ... \
idiot\n"
/*--------------------------> FUNCTION PROTOTYPES <---------------------------*/

void	error_simple(t_msh *msh, char *msg, int exit_code);
void	error_complex(t_msh *msh, char *msg, char *param, int exit_code);
int		msh_error(t_msh *msh, char *msg, char *param, int ret_value);

int		check_syntax_error_quotes(t_msh *msh);

#endif