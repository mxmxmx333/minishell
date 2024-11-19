/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:56:23 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/19 10:09:25 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_lonelys(t_msh *msh)
{
	t_tok	*tmp;
	t_tok	*delete;
	t_tok	*prev;

	tmp = msh->words;
	while (tmp)
	{
		if (tmp->lonely && str_is_empty(tmp->content))
		{
			if (tmp == msh->words)
				msh->words = msh->words->next;
			else
				prev->next = tmp->next;
			delete = tmp;
			tmp = tmp->next;
			destroy_tok_node(NULL, delete);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
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
	remove_lonelys(msh);
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
