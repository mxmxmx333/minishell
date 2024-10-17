/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:08:27 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/17 13:51:34 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	takes a string fragment and processes it into a token

	currently it just adds the string to the list. in the future it will 
	process the token properly
*/
void	process_fragment(t_msh *msh, char *fragment, int type)
{
	t_tok	*new;

	if (!fragment)
		return (error_simple(msh, M_ERR, EXIT_FAILURE));
	new = ft_calloc(sizeof(t_tok), 1);
	if (!new)
		return (free(fragment), error_simple(msh, M_ERR, EXIT_FAILURE));
	add_tok_node(msh, new);
	new->content = fragment;
	new->type = type;
	if (!new->content)
		return (free(fragment), error_simple(msh, M_ERR, EXIT_FAILURE));
}

static char	*handle_pipe(t_msh *msh, char *position)
{
	process_fragment(msh, ft_strdup("|"), PIPE);
	return (position + 1);
}

/* 
	takes the current position in the processed input string(cmd_line)
	it will process the next fragment and set token (tokens)
	and then return the offset after processing the fragment
*/
char	*put_token_str(t_msh *msh, char *position)
{
	char	*start;

	if (!position || !*position || str_is_empty(position))
		return (NULL);
	position = skip_whitespace(position);
	if (is_redirection(*position))
		return (handle_redirection(msh, position));
	if (*position == '|')
		return (handle_pipe(msh, position));
	start = position;
	while (*position && !is_end_token(*position))
	{
		if (*position == '\"' || *position == '\'')
			position = ret_next_twin(position);
		position++;
	}
	process_fragment(msh, ft_strndup(start, position - start), WORD);
	return (position);
}
