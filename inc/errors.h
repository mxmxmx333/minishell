/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:53:37 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/19 14:14:17 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

/*-----------------------------> ERROR MESSAGES <-----------------------------*/

/* FATAL ERRORS */

/* Malloc failure */
# define M_ERR "Fatal Error: Insufficient memory!\n"

/* EXECUTION ERRORS */

/* Permission denied*/
# define PER_ERR ": permission denied\n"
/* Is a directory */
# define DIR_ERR ": is a directory\n"
/* No such file or directory */
# define NODF_ERR ": no such file or directory\n"
/* Command not found*/
# define CMDNF_ERR ": command not found\n"


/*--------------------------> FUNCTION PROTOTYPES <---------------------------*/

void	error_simple(t_msh *msh, char *msg, int exit_code);
void	error_complex(t_msh *msh, char *msg, char *param, int exit_code);

#endif