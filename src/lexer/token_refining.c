/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_refining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:01:27 by mbonengl          #+#    #+#             */
/*   Updated: 2024/12/10 16:28:32 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	refine pipes: 
*/
int	ref_pipe(t_msh *msh, t_tok *current)
{
	if (current->type == PIPE)
	{
		if (!current->next)
			return (display_tok_err(msh, SYN_ERR_UNEXP_TOK, "newline"), 2);
		else if (current->next->type == PIPE)
			return (display_tok_err(msh, SYN_ERR_UNEXP_TOK, "|"), 2);
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
			return (display_tok_err(msh, SYN_ERR_UNEXP_TOK, "newline"), 2);
		else if (current->next->type != WORD)
			return (display_tok_err(msh, SYN_ERR_UNEXP_TOK, \
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
	if (tok->type == PIPE)
		return (display_tok_err(msh, SYN_ERR_UNEXP_TOK, "|"), 2);
	while (tok)
	{
		if (ref_redir(msh, tok) || ref_pipe(msh, tok))
			return (2);
		tok = neo_expand(msh, tok);
		if (!tok)
			return (3);
		tok = tok->next;
	}
	return (0);
}
