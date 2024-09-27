/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:28:31 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/27 15:22:31 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char c)
{
	return (c == '<' || c == '>');
}

/* 
	we enter this function, if we are on a < or > character

	syntax should have been checked before, so we can assume, that there will
	be a file / limiter name after the redirection character

	function will implement that token, and return the position after the file

*/

static int	redi_type(char *pos, t_tok *new)
{
	if (*pos == '<')
	{
		if (*(pos + 1) == '<')
		{
			new->type = HERE_DOC;
			return (2);
		}
		new->type = REDI_IN;
		return (1);
	}
	else if (*pos == '>')
	{
		if (*(pos + 1) == '>')
		{
			new->type = REDI_AOUT;
			return (2);
		}
		new->type = REDI_TOUT;
		return (1);
	}
	return (0);
}

static char	*redir_file(t_msh *msh, char *pos, t_tok *new)
{
	char 	*start;
		
	pos = skip_whitespace(pos);
	start = pos;
	while (*pos && !is_end_token(*pos))
	{
		if (*pos == '\"' || *pos == '\'')
			pos = ret_next_twin(pos);
		pos++;
	}
	new->file = ft_strndup(start, pos - start);
	if (!new->file)
		return (error_simple(msh, M_ERR, EXIT_FAILURE), NULL);
	return (pos);
}

char	*handle_redirection(t_msh *msh, char *pos)
{
	t_tok 		*new;
	
	new = create_tok_node(msh);
	if (!new)
		return (NULL);
	add_tok_node(msh, new);
	pos += redi_type(pos, new);
	return (redir_file(msh, pos, new));
}
