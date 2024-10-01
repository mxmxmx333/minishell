/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:49:46 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/01 16:14:06 by nicvrlja         ###   ########.fr       */
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

#endif