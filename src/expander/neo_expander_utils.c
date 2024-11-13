/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:34:46 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/13 20:27:46 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	inserts current into old to replace replace
*/
t_tok	*insert_new_tokens(t_tok **old, t_tok *current, t_tok *replace)
{
	t_tok	*prev;
	t_tok	*next;

	if (*old == replace)
		prev = NULL;
	else
	{
		prev = *old;
		while (prev->next != replace)
			prev = prev->next;
	}
	next = replace->next;
	if (prev)
		prev->next = current;
	else
		*old = current;
	while (current && current->next)
		current = current->next;
	current->next = next;
	free(replace->content);
	free(replace);
	return (current);
}

t_tok	*new_token(t_tok *current, t_msh *msh, char *content, int type)
{
	t_tok	*new;

	if (!content)
		return (clear_tok_list(current), error_simple(msh, M_ERR, 1), NULL);
	new = ft_calloc(1, sizeof(t_tok));
	if (!new)
		return (free(content), clear_tok_list(current), 
				error_simple(msh, M_ERR, 1), NULL);
	new->content = content;
	new->type = type;
	return (new);
}

t_tok	*copy_token(t_msh *msh, t_tok *tok)
{
	t_tok	*new;

	new = ft_calloc(1, sizeof(t_tok));
	if (!new)
		return (error_simple(msh, M_ERR, 1), NULL);
	new->content = ft_strdup(tok->content);
	if (!new->content)
		return (free(new), error_simple(msh, M_ERR, 1), NULL);
	new->type = tok->type;
	new->splitfile = tok->splitfile;
	new->lonely = tok->lonely;
	if (*tok->content == '$')
		new->expander = 1;
	return (new);
}
