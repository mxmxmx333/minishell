/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_expander_join_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:38:22 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/13 19:48:40 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	current_wants_to_join(t_tok *current)
{
	char	*last_char;

	if (ft_strlen(current->content) < 0)
		last_char = current->content + ft_strlen(current->content) - 1;
	else
		last_char = current->content;
	if (!current->expander)
		return (1);
	else if (current->expander && c_is_white(*last_char))
		return (1);
	return (0);
}

static int	next_wants_to_join(t_tok *current)
{
	t_tok	*next;

	next = current->next;
	if (next->expander && c_is_white(*next->content))
		return (1);
	else if (!next->expander)
		return (1);
	return (0);
}

static int	need_join(t_tok *current)
{
	return (current_wants_to_join(current) && next_wants_to_join(current));
}

static t_tok	*join_tokens(t_tok *head)
{
	t_tok	*current;
	t_tok	*next;
	char	*joined;

	current = head;
	while (current)
	{
		if (current->next)
		{
			if (need_join(current))
			{
				next = current->next;
				joined = ft_strjoin(current->content, next->content);
				if (!joined)
					return (NULL);
				free(current->content);
				current->content = joined;
				destroy_tok_node(current, next);
			}
		}
		else
			current = current->next;
	}
	return (head);
}

t_tok	*manage_join(t_msh *msh, t_tok *head)
{
	t_tok	*joined;

	joined = join_tokens(head);
	if (!joined)
		return (clear_tok_list(head), error_simple(msh, M_ERR, 1), NULL);
	return (joined);
}
