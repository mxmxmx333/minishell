/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_refining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:01:27 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/04 16:38:18 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_expander_flags(t_msh *msh)
{
	t_tok	*tok;

	tok = msh->tokens;
	while (tok)
	{
		if (tok->type == WORD && (strchr(tok->content, '"' ) || \
			strchr(tok->content, '\'')))
			tok->splitme = 0;
		tok = tok->next;
	}
}

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
	if (tok->type == PIPE)
		return (display_tok_err(SYN_ERR_UNEXP_TOK, "|"), 2);
	while (tok)
	{
		if (ref_redir(msh, tok) || ref_pipe(tok))
			return (2);
		tok->content = expand(msh, tok->content);
		if (!tok->content)
			error_simple(msh, M_ERR, EXIT_FAILURE);
		if (tok->file && tok->type != HERE_DOC)
		{
			tok->file = expand(msh, tok->file);
			if (!tok->file)
				error_simple(msh, M_ERR, EXIT_FAILURE);
		}
		tok = tok->next;
	}
	return (0);
}
