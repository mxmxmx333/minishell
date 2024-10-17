/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:49:46 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/17 12:34:46 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This file contains is the header file for the cons directory, which contains
**	the part of the minishell, that is responsible for displaying the prompt in
**	the terminal. As well as reading from readline and rerouting the input to the
**	lexer for tokenization.
*/

#ifndef CONSOLE_H
# define CONSOLE_H

# include "minishell.h"

int		create_prompt(t_msh *msh);
char	*get_hostname(void);
int		write_history_custom(t_msh *msh, char *filename, char *line);
int		load_history(t_msh *msh, char *filename);

#endif