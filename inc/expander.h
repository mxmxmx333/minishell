/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:56:33 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/02 18:32:15 by mbonengl         ###   ########.fr       */
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


typedef	enum e_expander_mode
{
	GEN,
	DUO,
	SGL
}	t_exmode;

char	*variable_finder(t_msh *msh, char *str);
char	*expand(t_msh *msh, t_tok *tok, char *str);

#endif