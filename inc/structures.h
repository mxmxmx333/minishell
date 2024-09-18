/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:25:41 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/18 16:16:23 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	This file contains all the structures used in the minishell project as well
	as the prototypes of the functions that manipulate these structures.
*/

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

/*-------------------------> VARIABLE linked list <--------------------------*/
typedef struct s_variables
{
	char				*v_name;
	char				*v_value;
	struct s_variables	*next;
}						t_var;

/*--------------------> ENVIRONMENT variable linked list <-------------------*/
typedef struct s_environment
{
	char					*v_name;
	char					*v_value;
	struct s_environment	*next;
}							t_env;

/*--------------------------> MINISHELL structure <--------------------------*/
typedef struct s_minishell
{
	t_env	*env;		//env variable list
	size_t	env_size;	//env varable list size
	t_var	*var;		//variable list
	size_t	var_size;	//variable list size
	char	*cur_dir;	//current directory
	char	*prompt;	//current prompt for console
}	t_msh;

/* ENVIRONMENT */

void	free_env_node(t_env **node);
void	clear_env(t_msh *msh);
void	add_env_node(t_msh *msh, t_env *node);
t_env	*create_env_node(t_msh *msh, char *env);
void	initialize_environment(t_msh *msh, char **env);

/* MINISHELL */

t_msh	*initialize_minishell(char **env);

#endif