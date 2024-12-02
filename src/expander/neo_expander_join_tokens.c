/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_expander_join_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:38:22 by mbonengl          #+#    #+#             */
/*   Updated: 2024/12/02 14:42:35 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_empty_var(t_tok *current)
{
	while (current->next)
	{
		if (str_is_empty(current->next->content) && current->next->expander)
			destroy_tok_node(current, current->next);
		if (current->next)
			current = current->next;
	}
}

static t_tok	*join_one_token(t_tok *current, t_tok *next)
{
	char	*joined;

	if (!next->expander)
		joined = ft_strjoin(current->content, next->content);
	else
		joined = ft_strjoin(current->content, skip_whitespace(next->content));
	if (!joined)
		return (NULL);
	free(current->content);
	current->content = joined;
	current->splitfile = next->splitfile;
	current->expander = next->expander;
	current->next = next->next;
	destroy_tok_node(current, next);
	return (current);
}

static t_tok	*join_tokens(t_tok *head)
{
	t_tok	*current;

	current = head;
	while (current)
	{
		if (current->next)
		{
			if (need_join(current))
			{
				current = join_one_token(current, current->next);
				if (!current)
					return (NULL);
			}
			else
			{
				trim_first_spaces(current);
				trim_first_spaces(current->next);
				current = current->next;
			}
		}
		else
			break ;
	}
	return (head);
}

t_tok	*manage_join(t_msh *msh, t_tok *head)
{
	t_tok	*joined;

	handle_empty_var(head);
	joined = join_tokens(head);
	if (!joined)
		return (clear_tok_list(head), error_simple(msh, M_ERR, 1), NULL);
	trim_spaces_in_the_end(joined);
	return (joined);
}
