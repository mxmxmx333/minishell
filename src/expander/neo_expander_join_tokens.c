/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_expander_join_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:38:22 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/14 16:50:59 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	current_wants_to_join(t_tok *current)
{
	char	*last_char;

	if (!current->expander)
		return (1);
	else
	{
		if (ft_strlen(current->content) > 0)
			last_char = current->content + ft_strlen(current->content) - 1;
		else
			last_char = current->content;
		if (c_is_white(*last_char))
		{
			last_char = current->content;
			while (!c_is_white(*last_char))
				last_char++;
			*last_char = '\0';
			return (0);
		}
		if (current->next->expander)
		{
			if (current->splitfile == current->next->splitfile)
				return (0);
		}
	}
	return (1);
}

static int	next_wants_to_join(t_tok *current)
{
	t_tok	*next;

	next = current->next;
	if (!next->expander)
		return (1);
	else
	{
		if (current->expander && current->splitfile == next->splitfile)
			return (0);
		if (c_is_white(*next->content))
			return (0);
	}
	return (1);

}

static int	need_join(t_tok *current)
{
	return (current_wants_to_join(current) && next_wants_to_join(current));
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

void	trim_first_spaces(t_tok *current)
{
	char	*start;

	if (!current->expander)
		return ;
	start = current->content;
	while (c_is_white(*start))
		start++;
	ft_memmove(current->content, start, ft_strlen(start) + 1);
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

void	trim_spaces_in_the_end(t_tok *joined)
{
	char	*last_char;

	while (joined->next)
		joined = joined->next;
	if (!joined->expander)
		return ;
	if (ft_strlen(joined->content) > 0)
		last_char = joined->content + ft_strlen(joined->content) - 1;
	else
		last_char = joined->content;
	while (c_is_white(*last_char))
	{
		*last_char = '\0';
		last_char--;
	}
}

t_tok	*manage_join(t_msh *msh, t_tok *head)
{
	t_tok	*joined;

	joined = join_tokens(head);
	if (!joined)
		return (clear_tok_list(head), error_simple(msh, M_ERR, 1), NULL);
	trim_spaces_in_the_end(joined);
	return (joined);
}
