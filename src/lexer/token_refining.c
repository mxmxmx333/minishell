/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_refining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:01:27 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/01 19:07:21 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	refine pipes: 
*/
int	ref_pipe(t_tok *current)
{
	if (current->type == PIPE)
	{
		if (!current->next)
			return (display_tok_err(SYN_ERR_UNEXP_TOK, "newline"), 2);
		else if (current->next->type == PIPE)
			return (display_tok_err(SYN_ERR_UNEXP_TOK, "|"), 2);
	}
	return (0);
}

/*
	refine redirections: 
*/
int	ref_redir(t_msh *msh, t_tok *current)
{
	if (isredi(current->type))
	{
		if (!current->next)
			return (display_tok_err(SYN_ERR_UNEXP_TOK, "newline"), 2);
		else if (current->next->type != WORD)
			return (display_tok_err(SYN_ERR_UNEXP_TOK, \
					current->next->content), 2);
		else
		{
			current->file = ft_strdup(current->next->content);
			if (!current->file)
				error_simple(msh, M_ERR, EXIT_FAILURE);
			destroy_tok_node(current, current->next);
		}
	}
	return (0);
}

int	refining_tokens(t_msh *msh)
{
	t_tok	*tok;

	tok = msh->tokens;
	while (tok)
	{
		if (ref_redir(msh, tok) || ref_pipe(tok))
			return (2);
		//expand
		//here_doc
		tok = tok->next;
	}
	return (0);
}
