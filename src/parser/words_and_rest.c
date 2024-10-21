/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_and_rest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:37:43 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/21 14:26:32 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_word_and_rest(t_msh *msh)
{
	if (msh->words)
		destroy_word(msh);
	if (msh->rest)
		destroy_rest(msh);
}

/* 
	destroys the words list, which contains the word tokens for the current 
	command
*/
void	destroy_word(t_msh *msh)
{
	t_tok	*tmp;

	while (msh->words)
	{
		tmp = msh->words;
		msh->words = msh->words->next;
		destroy_tok_node(NULL, tmp);
	}
	msh->words = NULL;
}

/* 
	Adds a word token to the words list
*/
void	add_word(t_msh *msh, t_tok *word)
{
	t_tok	*tmp;

	word->next = NULL;
	if (!msh->words)
	{
		msh->words = word;
	}
	else
	{
		tmp = msh->words;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = word;
	}
}

/* 
	destroys the rest list, which contains the redirection tokens for
	the current command
*/
void	destroy_rest(t_msh *msh)
{
	t_tok	*tmp;

	while (msh->rest)
	{
		tmp = msh->rest;
		msh->rest = msh->rest->next;
		destroy_tok_node(NULL, tmp);
	}
	msh->rest = NULL;
}

/* 
	Adds a redirection token to the rest list
*/
void	add_rest(t_msh *msh, t_tok *rest)
{
	t_tok	*tmp;

	rest->next = NULL;
	if (!msh->rest)
	{
		msh->rest = rest;
	}
	else
	{
		tmp = msh->rest;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = rest;
	}
}
