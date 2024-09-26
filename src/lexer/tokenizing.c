/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:08:27 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 18:56:16 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	takes a string fragment and processes it into a token

	currently it just adds the string to the list. in the future it will 
	process the token properly
*/
void	process_fragment(t_msh *msh, char *fragment)
{
	t_tok	*new;

	if (!fragment)
		return (error_simple(msh, M_ERR, EXIT_FAILURE));
	new = create_tok_node(msh);
	add_tok_node(msh, new);
	new->content = ft_strdup(fragment);
	new->type = WORD;
	if (!new->content)
		return (error_simple(msh, M_ERR, EXIT_FAILURE), free(fragment));
	free(fragment);
}

void	put_end_token(t_msh *msh)
{
	t_tok	*new;

	new = create_tok_node(msh);
	add_tok_node(msh, new);
	new->content = ft_strdup("");
	new->type = END;
}

/* 
	takes the current position in the processed input string(cmd_line)
	it will process the next fragment and set token (tokens)
	and then return the offset after processing the fragment
*/
char	*put_token_str(t_msh *msh, char *position)
{
	char	*start;

	if (!position || !*position)
		return (NULL);
	if (str_is_empty(position))
		return (put_end_token(msh), NULL);
	start = position;
	while (*position && !is_token_end(*position))
	{
		if (*position == '\"' || *position == '\'')
			position = ret_next_twin(position);
		position++;
	}
	process_fragment(msh, ft_strndup(start, position - start));
	return (position);
}
