/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:56:33 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/16 17:23:50 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This file contains is the header file for the xpand directory, which contains
**	the part of the minishell, that is responsible for expanding the tokens that
**	are passed to it.
*/

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef enum e_expander_mode
{
	GEN,
	DUO,
	SGL
}	t_exmode;

/*-----------------------------> Expander utils <-----------------------------*/
int		is_varname_break(char c);
char	*variable_finder_value(t_msh *msh, char *str);
int		get_quote_len(t_msh *msh, char *str, char quote);
int		get_len_not_var_in_quote(char *str, char quote);
int		get_len_not_var_in_part(char *str);
int		get_part_len(t_msh *msh, char *str);
int		get_single_len(char *str);

/*-------------------------> Expander main function <-------------------------*/

char	*expand(t_msh *msh, char *str);

#endif