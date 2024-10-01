/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:25:41 by mbonengl          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/01 16:52:47 by mbonengl         ###   ########.fr       */
=======
/*   Updated: 2024/10/01 16:47:06 by nicvrlja         ###   ########.fr       */
>>>>>>> dev_ni
/*                                                                            */
/* ************************************************************************** */

/*
	This file contains all the structures used in the minishell project as well
	as the prototypes of the functions that manipulate these structures.
*/

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

/*------------------------------> TOKEN TYPES <-------------------------------*/

typedef enum e_typ
{
	END,
	PIPE,
	REDI_IN,
	REDI_TOUT,
	REDI_AOUT,
	HERE_DOC,
	WORD,
	CMD,
	ARG
}	t_e_typ;

/*--------------------------> TOKENS linked list <---------------------------*/
/*
	*content;
	*file;
	type;
	expand;
	*next;
*/
typedef struct s_tokens
{
	char			*content;	//token content
	char			*file;		//file name
	t_e_typ			type;		//type of token
	int				expand;		//mode for expansion
	struct s_tokens	*next;
}	t_tok;

/*-------------------------> VARIABLE linked list <--------------------------*/
/*
	*v_name;
	*v_value;
	*next;
*/
typedef struct s_variables
{
	char				*v_name;
	char				*v_value;
	struct s_variables	*next;
}	t_var;

/*--------------------> ENVIRONMENT variable linked list <-------------------*/
/*
	*v_name;
	*v_value;
	*next;
*/
typedef struct s_environment
{
	char					*v_name;
	char					*v_value;
	struct s_environment	*next;
}	t_env;

/*--------------------------> MINISHELL structure <--------------------------*/
/* 
	**export
	**paths
	*exe_path
	*env
	env_size
	*var
	var_size
	*cur_dir
	*username
	*hostname
	*home_dir
	*prompt
	*cur_cmd_line
	*tokens
*/
typedef struct s_minishell
{
	char	**export;		//exported list for execution
	char	**paths;		//path list
	char	*exe_path;		//executable path
	t_env	*env;			//env variable list
	size_t	env_size;		//env varable list size
	t_var	*var;			//variable list
	size_t	var_size;		//variable list size
	char	*cur_dir;		//current directory
	char	*username;		//username
	char	*hostname;		//hostname
	char	*home_dir;		//home directory
	char	*prompt;		// current prompt for console
	char	*cur_cmd_line;	//current input
	t_tok	*tokens;		//tokens list
	int		status;			//exit code
}	t_msh;

#endif