/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:24:08 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/21 14:19:38 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*----------------------------> Word separation <----------------------------*/

void	get_words_and_rest(t_msh *msh);
void	add_rest(t_msh *msh, t_tok *rest);
void	destroy_rest(t_msh *msh);
void	add_word(t_msh *msh, t_tok *word);
void	destroy_word(t_msh *msh);
void	destroy_word_and_rest(t_msh *msh);

/*---------------------------------> Parser <---------------------------------*/
void	parse_tokens(t_msh *msh);
void	destroy_token_part(t_msh *msh, t_tok *tmp);

/*--------------------------> Creating Execu-Table <--------------------------*/
void	add_exeutable(t_msh *msh);
void	convert_word_list(t_msh *msh, t_exec *table);
int		get_args_size(t_tok *words);
int		put_words(t_msh *msh, char **args, t_tok *words, size_t i);
t_exec	*create_executable(t_msh *msh);
void	destroy_executable(t_msh *msh);

/*--------------------------------> Printing <--------------------------------*/

void	print_words_and_rest(t_msh *msh);
void	print_token(t_tok *token);

#endif