/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:53:37 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/29 16:46:03 by mbonengl         ###   ########.fr       */
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
# define M_ERR "Fatal Error: Insufficient memory!"

/* 
	EXECUTION ERRORS <-----------------------------------------------------
*/

/* Permission denied*/
# define PER_ERR ": permission denied"
/* Is a directory */
# define DIR_ERR ": is a directory"
/* No such file or directory */
# define NODF_ERR ": no such file or directory"
/* Command not found*/
# define CMDNF_ERR ": command not found"

/* 
	SYNTAX ERRORS <-----------------------------------------------------
*/

/* Syntax Error: Unmached quotes */
# define SYN_QUO_ERR "syntax error: unmatched quotes: "
/* Syntax Error: Unexpected Token (e.g. <<> or || ) */
# define SYN_ERR_UNEXP_TOK "syntax error near unexpected token: `"
/* 
	Function specific 
		exit with 42!
	super fatal ERRORS 
*/

/* Error message, if Pathfinder recieves NULL input */
# define SUFA_ERR_PATHFINDER "ERR: Pathfinder failed, you tried to input NULL ... \
idiot"

/* Error message, if Pathfinder recieves NULL input */
# define SUFA_ERR_SYX_Q_ERR "ERR: You tried to check syntax (quotes) of NULL ... \
idiot"
/*--------------------------> FUNCTION PROTOTYPES <---------------------------*/

void	error_simple(t_msh *msh, char *msg, int exit_code);
void	error_complex(t_msh *msh, char *msg, char *param, int exit_code);
void	error_complex_tok(t_msh *msh, char *msg, char *param, int exit_code);

void	check_syntax_error_quotes(t_msh *msh);
void	check_token_err_redi(t_msh *msh);

#endif	