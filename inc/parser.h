/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:24:08 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/19 16:28:29 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*-----------------------------> Word separation <-----------------------------*/

void	get_words_and_rest(t_msh *msh);
void	add_rest(t_msh *msh, t_tok *rest);
void	destroy_rest(t_msh *msh);
void	add_word(t_msh *msh, t_tok *word);
void	destroy_word(t_msh *msh);
void	destroy_word_and_rest(t_msh *msh);

/*----------------------------------> Parser <----------------------------------*/
void	parse_tokens(t_msh *msh);
void	destroy_token_part(t_msh *msh, t_tok *tmp);

/*---------------------------------> Printing <---------------------------------*/

void	print_words_and_rest(t_msh *msh);
void	print_token(t_tok *token);

#endif