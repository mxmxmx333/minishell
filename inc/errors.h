/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:53:37 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/13 14:24:08 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

/*-----------------------------> ERROR MESSAGES <-----------------------------*/

/* 
	FATAL ERRORS <-----------------------------------------------------
*/

/* Prompt error*/
# define PR_ERR "Fatal Error: Failed to create prompt!\n"

/* Malloc failure */
# define M_ERR "Fatal Error: Insufficient memory!\n"

/* File descriptor error */
# define FD_ERR "Fatal Error: Unable to open file!\n"

/* 
	EXECUTION ERRORS <-----------------------------------------------------
*/

/* permission denied*/
# define PER_ERR ": Permission denied"
/* Open permission denied*/
# define O_PER_ERR ": Permission denied"
/* Is a directory */
# define DIR_ERR ": Is a directory"
/* No such file or directory */
# define NODF_ERR ": No such file or directory"
/* Command not found*/
# define CMDNF_ERR ": command not found"
/* Fatal: Failed to create Pipe */
# define FATAL_ERR_PIPE "Fatal Error: Failed to create Pipe!\n"

/* Fatal: Failed to create child process */
# define FATAL_ERR_FORK "Fatal Error: Failed to create child process!\n"
/* 
	SYNTAX ERRORS <-----------------------------------------------------
*/

/* Syntax Error: Unmached quotes */
# define SYN_QUO_ERR "syntax error: unmatched quotes: "
/* Syntax Error: Unexpected Token (e.g. <<> or || ) */
# define SYN_ERR_UNEXP_TOK "syntax error near unexpected token `"
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
void	display_tok_err(t_msh *msh, char *p1, char *p2);
void	dis_func_err(t_msh *msh, char *cmdname, char *arg, char *errmsg);
void	here_doc_error(int line, char *limiter);

int		check_syntax_error_quotes(t_msh *msh);
void	check_token_err_redi(t_msh *msh);
void	check_token_err_pipe(t_msh *msh);

#endif	