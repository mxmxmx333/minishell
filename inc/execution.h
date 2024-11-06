/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:50 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/06 17:53:30 by nicvrlja         ###   ########.fr       */
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

/*---------------------------------> utils <---------------------------------*/

int		pathfinder(t_msh *msh, char *path);
void	destroy_exe_path(t_msh *msh);

/*------------------------------> structuring <------------------------------*/

void	prepare_execution(t_msh *msh);
void	finished_execution(t_msh *msh);

/*-----------------------------> implementation <-----------------------------*/

int		execute_command(t_msh *msh, t_exec *current);

/*--------------------------------> wrappers <--------------------------------*/

void	wrppd_dup2(t_msh *msh, int old_fd, int new_fd);
void	wrppd_close(t_msh *msh, int fd);
void	wrppd_pipe(t_msh *msh, int *fd);
int		wrppd_fork(t_msh *msh);
int		wrppd_open(t_msh *msh, char *path, int flags);
int		wrppd_open_builtin(t_msh *msh, char *path, int flags);
void	wrpped_close_builtin(t_msh *msh, int fd);

/*------------------------------> redirections <------------------------------*/

//handlers: are on top level of a single execution

void	create_out_pipe(t_msh *msh, t_exec *current);
void	redirect_outpipe(t_msh *msh, t_exec *current);
void	redirect_inpipe(t_msh *msh, t_exec *current);
void	redirect_output(t_msh *msh, t_tok *redirections);
void	redirect_input(t_msh *msh, t_tok *redirections);
void	close_pipe(t_msh *msh, int fd[2]);
void	close_previous_pipe(t_msh *msh, t_exec *current);
void	close_both_pipes(t_msh *msh, t_exec *current);

/*--------------------------------> conditions <------------------------------*/

int		is_parent(int pid);

/*------------------------------> execution <------------------------------*/

int		execution(t_msh *msh);
void	set_builtin_function(t_exec *exec);
void	execute_builtin(t_msh *msh, t_exec *exec);

#endif