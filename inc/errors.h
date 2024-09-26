/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:53:37 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 18:48:46 by mbonengl         ###   ########.fr       */
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

/* Function specific ERRORS */

/* Error message, if Pathfinder recieves NULL input */
# define PATHFINDER_ERR "ERROR: Pathfinder failed, you tried to input NULL\n"
/*--------------------------> FUNCTION PROTOTYPES <---------------------------*/

void	error_simple(t_msh *msh, char *msg, int exit_code);
void	error_complex(t_msh *msh, char *msg, char *param, int exit_code);

void	check_syntax_error_quotes(t_msh *msh);

#endif