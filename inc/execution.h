/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:50 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/19 12:30:51 by mbonengl         ###   ########.fr       */
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

void	convert_exp(t_msh *msh); //export
void	destroy_exp(t_msh *msh); //export

void	extract_paths(t_msh *msh); //paths
void	destroy_paths(t_msh *msh); //paths

/*---------------------------------> utils <----------------------------------*/

int		pathfinder(t_msh *msh, char *path);
void	destroy_exe_path(t_msh *msh);

/*------------------------------> structuring <-------------------------------*/

void	prepare_execution(t_msh *msh);
void	finished_execution(t_msh *msh);

#endif