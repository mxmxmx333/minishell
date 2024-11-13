/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_expander_split_vars.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:37:30 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/13 19:49:01 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	$ signs out of quotes are breakpoints will split at these points into
	individual tokens
*/
void	split_next_var(t_msh *msh, t_tok *clear, t_tok *current)
{
	char	*breakpoint;

	breakpoint = current->content;
	
	if (*breakpoint == '$')
	{
		current->expander = 1;
		breakpoint++;
		while (*breakpoint && !is_varname_break(*breakpoint))
			breakpoint++;
	}
	else
	{
		current->expander = 0;
		while (*breakpoint && *breakpoint != '$')
		{
			if (*breakpoint == '\'' || *breakpoint == '\"')
				breakpoint = ret_next_twin(breakpoint);
			breakpoint++;
		}
	}
	current->next = new_token(clear, msh, ft_strdup(breakpoint), WORD);
	*breakpoint = '\0';
}

void	split_expanded_variable(t_tok *current)
{
	char	*breakpoint;
	t_tok	*new;

	breakpoint = current->content;
	while (*breakpoint)
	{
		breakpoint = skip_whitespace(breakpoint);
		while (!c_is_white(*breakpoint))
			breakpoint++;
	}
	new = ft_calloc(1, sizeof(t_tok));
	if (!new)
		return ;
	new->content = ft_strdup(skip_whitespace(breakpoint));
	if (!new->content)
		return (free(new));
	new->type = WORD;
	new->expander = 1;
	current->next = new;
	*breakpoint = '\0';
}
