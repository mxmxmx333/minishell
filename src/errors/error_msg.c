/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:27:56 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/13 14:29:35 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This function will display an error message on stderr and exit the program
	safeley.

	msh: minishell structure to destroy at exit
	msg: error message to display on stderr
	exit_code: code to exit the program with
*/
void	error_simple(t_msh *msh, char *msg, int exit_code)
{
	char	*error_msg;

	error_msg = ft_strjoin("msh: ", msg);
	if (!error_msg)
	{
		ft_putstr_fd("Superfatal Malloc Error\n", STDERR_FILENO);
		destroy_minishell(msh);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free(error_msg);
	destroy_minishell(msh);
	exit(exit_code);
}

/*
	This function will display an error message on stderr and exit the program
	safeley.
	
	Same as error_complex, but adds a "'" to the end of the error message.
	Because `param' is how the error is displayed by bash.
*/
void	error_complex_tok(t_msh *msh, char *msg, char *param, int exit_code)
{
	char	*error_msg;

	ft_putstr_fd("msh: ", STDERR_FILENO);
	error_msg = ft_strjoin_three(param, msg, "'");
	if (!error_msg)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	free(error_msg);
	destroy_minishell(msh);
	exit(exit_code);
}

/*
	This function will display an error message on stderr and exit the program
	safeley.

	Same as error_simple, but adds a param to the error message.
	e-G "msh: ->abc<-: no such file or directory"
	Can also be used in different order, since it uses putendl_fd.
*/
void	error_complex(t_msh *msh, char *msg, char *param, int exit_code)
{
	char	*error_msg;

	error_msg = ft_strjoin_three("msh: ", param, msg);
	if (!error_msg)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	free(error_msg);
	destroy_minishell(msh);
	exit(exit_code);
}

void	display_tok_err(t_msh *msh, char *p1, char *p2)
{
	char	*err_msg;
	char	*tmp;

	err_msg = ft_strjoin_three("msh: ", p1, p2);
	if (!err_msg)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	tmp = err_msg;
	err_msg = ft_strjoin(err_msg, "'\n");
	free(tmp);
	if (!err_msg)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	free(err_msg);
}

/*
	Function to display error message, useful for erros in builtin functions 
	it prints in format msh: $cmdname: $arg: $errmsg
*/
void	dis_func_err(t_msh *msh, char *cmdname, char *arg, char *errmsg)
{
	char	*err_msg;
	char	*tmp;

	err_msg = ft_strjoin_three("msh: ", cmdname, arg);
	if (!err_msg)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	tmp = err_msg;
	err_msg = ft_strjoin_three(err_msg, ": ", errmsg);
	free(tmp);
	if (!err_msg)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	tmp = err_msg;
	err_msg = ft_strjoin(err_msg, "\n");
	free(tmp);
	if (!err_msg)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	free(err_msg);
}
