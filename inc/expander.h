/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:56:33 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/18 09:40:41 by mbonengl         ###   ########.fr       */
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
int		ft_strnrealcmp(char *s1, char *s2, int n);
int		splitme_len(char *str);
void	add_trimmed_var(char *exp, char *v_value);
void	put_part_expander(t_msh *msh, char *str, char *exp);
t_tok	*expand_redirect(t_msh *msh, t_tok *tok);
t_tok	*copy_token(t_msh *msh, t_tok *tok);
t_tok	*new_token(t_tok *current, t_msh *msh, char *content, int type);
t_tok	*insert_new_tokens(t_tok **old, t_tok *current, t_tok *replace);

/*--------------------------> Splitting variables <---------------------------*/

void	split_expanded_variable(t_tok *current, int varflag);
void	split_next_var(t_msh *msh, t_tok *clear, t_tok *current);

/*------------------------------> join Tokens <-------------------------------*/

t_tok	*manage_join(t_msh *msh, t_tok *head);
void	trim_first_spaces(t_tok *current);
void	trim_spaces_in_the_end(t_tok *joined);

/*-------------------------> Expander main function <-------------------------*/

char	*expand(t_msh *msh, char *str);
t_tok	*neo_expand(t_msh *msh, t_tok *tok);
int		need_join(t_tok *current);

#endif