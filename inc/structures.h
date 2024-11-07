/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:25:41 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/07 14:03:59 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	This file contains all the structures used in the minishell project as well
	as the prototypes of the functions that manipulate these structures.
*/

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

typedef struct s_minishell	t_msh;

/*-------------------------------> HERE_DOCS <--------------------------------*/

typedef struct s_here_doc
{
	char				*file;
	struct s_here_doc	*next;
}	t_hdoc;

/*------------------------------> TOKEN TYPES <-------------------------------*/

typedef enum e_typ
{
	NEWL,
	PIPE,
	REDI_IN,
	REDI_TOUT,
	REDI_AOUT,
	HERE_DOC,
	WORD,
	CMD,
	ARG,
}	t_e_typ;

/*--------------------------> TOKENS linked list <----------------------------*/
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
	int				splitme;	//mode for expansion
	int				splitfile;
	int				expander;
	struct s_tokens	*next;
}	t_tok;

/*-----------------------------> EXECUTE TABLE <------------------------------*/

/*
	*cmd;
	*builtin;
	**args;
	*redirections;
	out_pipe[2];
	*next;
	*prev;
*/
typedef struct s_execute_table
{
	char					*cmd;
	int						(*builtin)(t_msh *, struct s_execute_table *, int);
	char					**args;
	t_tok					*redirections;
	bool					pipe;
	int						out_pipe[2];
	struct s_execute_table	*next;
	struct s_execute_table	*prev;
}	t_exec;

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
	exit_code
*/
typedef struct s_minishell
{
	t_tok	*rest;			//rest of the tokens
	t_tok	*words;			//words list
	t_exec	*exec_table;	//execution table
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
	char	status_char[4];    //exit_code_printable
	int		last_pid;		//last process id
	t_hdoc	*here_doc;		//here document list
}	t_msh;

#endif