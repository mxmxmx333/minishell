/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:19:04 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/06 18:33:38 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This file contains is the header file for the lex directory, which contains
**	the part of the minishell, that is responsible for tokenizing the input that
**	is passed to it.
*/

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/*-------------------------------> EXPAND TYPES <-----------------------------*/

/*---------------------------> FUNCTION PROTOTYPES <--------------------------*/

/*
	Tokens linked list utils <--------------------------------------------------
*/

t_tok	*create_tok_node(t_msh *msh);
void	add_tok_node(t_msh *msh, t_tok *new);
void	destroy_tok_node(t_tok *prev, t_tok *tok);
void	destroy_tokens(t_msh *msh);

/*
	Interpret utils <----------------------------------------------------------
*/

int		is_end_token(char c);
char	*ret_next_twin(char *position);
char	*skip_whitespace(char *position);
int		is_redirection(char c);
int		isredi(int type);

/*
	Error handling <-----------------------------------------------------------
*/

int		check_syntax_error_quotes(t_msh *msh);
void	check_token_err_redi(t_msh *msh);
void	check_token_err_pipe(t_msh *msh);

/*
	Tokenizing <---------------------------------------------------------------
*/

char	*put_token_str(t_msh *msh, char *position);
char	*handle_redirection(t_msh *msh, char *pos);
void	put_content_to_redi(t_msh *msh);
int		refining_tokens(t_msh *msh);
void	add_expander_flags(t_msh *msh);

/*
	Here_doc <------------------------------------------------------------------
*/

void	destroy_here_doc(t_msh *msh);
void	add_here_doc(t_msh *msh, char *file);
void	gen_here_doc(t_msh *msh, t_tok *tok);

#endif