/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_expander_join_tokens_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:38:38 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/18 09:41:03 by mbonengl         ###   ########.fr       */
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

int	need_join(t_tok *current)
{
	return (current_wants_to_join(current) && next_wants_to_join(current));
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
