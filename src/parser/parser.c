/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:56:23 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/05 13:48:12 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FIXME: DO i really need this function?
void	destroy_token_part(t_msh *msh, t_tok *tmp)
{
	t_tok	*delete;

	if (!tmp)
		return (destroy_tokens(msh));
	while (msh->tokens != tmp)
	{
		delete = msh->tokens;
		msh->tokens = msh->tokens->next;
		destroy_tok_node(NULL, delete);
	}
}

void	get_words_and_rest(t_msh *msh)
{
	t_tok	*tmp;
	t_tok	*transfer;

	tmp = msh->tokens;
	while (tmp && tmp->type != PIPE && tmp->type != NEWL)
	{
		transfer = tmp;
		tmp = tmp->next;
		if (transfer->type == WORD)
			add_word(msh, transfer);
		else
			add_rest(msh, transfer);
	}
	msh->tokens = tmp;
}

void	parse_tokens(t_msh *msh)
{
	t_tok	*tmp;

	while (1)
	{
		if (msh->tokens->type == PIPE)
		{
			tmp = msh->tokens;
			msh->tokens = msh->tokens->next;
			destroy_tok_node(NULL, tmp);
		}
		get_words_and_rest(msh);
		add_exeutable(msh);
		if (!msh->tokens || msh->tokens->type == NEWL)
			break ;
	}
	destroy_word_and_rest(msh);
}
