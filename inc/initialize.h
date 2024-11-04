/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:58:38 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/30 14:08:23 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This file contains is the header file for the pars directory, which contains
**	the part of the minishell, that is responsible for parsing the tokens that
**	are passed to it.
*/

#ifndef INITIALIZE_H
# define INITIALIZE_H

# include "minishell.h"

/* 
	INIT MINISHELL <-----------------------------------------------------
*/
t_msh	*initialize_minishell(char **env);
void	destroy_minishell(t_msh *msh);
int		*get_status(int *msh_status);

/* 
	ENV LIST <-----------------------------------------------------------
*/
void	free_env_node(t_env **node);
void	destroy_env(t_msh *msh);
void	add_env_node(t_msh *msh, t_env *node);
t_env	*create_env_node(t_msh *msh, char *env);
void	initialize_environment(t_msh *msh, char **env);
size_t	env_size(t_msh *msh);

#endif