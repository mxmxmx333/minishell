/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:31:28 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/19 16:34:49 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTING_H
# define PRINTING_H

# include "minishell.h"

char	*get_type(int type);
void	print_tokens(t_msh *msh);
void	print_token(t_tok *token);
void	print_words_and_rest(t_msh *msh);

#endif