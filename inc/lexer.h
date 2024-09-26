/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:19:04 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 19:08:03 by mbonengl         ###   ########.fr       */
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

/*------------------------------> TOKEN TYPES <-------------------------------*/

# define END 0
# define PIPE 1
# define REDIR 2
# define HERE_DOC 3
# define WORD 4
# define CMD 5
# define ARG 6


/*------------------------------> EXPAND TYPES <-------------------------------*/

/*------------------------------> TOKEN TYPES <-------------------------------*/


/*------------------------------> FUNCTION PROTOTYPES <-----------------------*/

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

/* 
	Error handling <-----------------------------------------------------------
*/

void	check_syntax_error_quotes(t_msh *msh);

/* 
	Tokenizing <---------------------------------------------------------------
*/

char	*put_token_str(t_msh *msh, char *position);





#endif