/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:23:41 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/11 13:37:18 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	creates a new token node, handles malloc errors, and returns it
*/
t_tok	*create_tok_node(t_msh *msh)
{
	t_tok	*new;

	new = (t_tok *)ft_calloc(sizeof(t_tok), 1);
	if (!new)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	return (new);
}

/* 
	destroys a token node safely, by freeing all its members, then the node
	in case node shall be removed from the middle of list, prev must be set to 
	the previous node
*/
void	destroy_tok_node(t_tok *prev, t_tok *tok)
{
	if (tok)
	{
		if (tok->content)
			free(tok->content);
		if (tok->file)
			free(tok->file);
		if (prev)
			prev->next = tok->next;
		free(tok);
	}
}

/*
	destroys all token nodes in the list, safely, by clearing the list and
	freeing each node and members, and setting the list to NULL
*/
void	destroy_tokens(t_msh *msh)
{
	t_tok	*tmp;
	t_tok	*prev;

	tmp = msh->tokens;
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		destroy_tok_node(NULL, prev);
	}
	msh->tokens = NULL;
}

/* 
	adds a new token node to the end of the list, if list is empty, the new node
	will be the first nodes
 */
void	add_tok_node(t_msh *msh, t_tok *new)
{
	t_tok	*tmp;

	if (!msh->tokens)
		msh->tokens = new;
	else
	{
		tmp = msh->tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	clear_tok_list(t_tok *tok)
{
	t_tok	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp);
	}
}
