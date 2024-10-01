/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:28:31 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/01 16:49:51 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	will put the redirection content into the token list as a string.
	( <, >, >>, << )
*/
static void	put_redi(t_msh *msh, t_tok *tok, int type)
{
	if (type == REDI_IN)
	{
		tok->content = ft_strdup("<");
		tok->type = REDI_IN;
	}
	else if (type == REDI_TOUT)
	{
		tok->content = ft_strdup(">");
		tok->type = REDI_TOUT;
	}
	else if (type == REDI_AOUT)
	{
		tok->content = ft_strdup(">>");
		tok->type = REDI_AOUT;
	}
	else if (type == HERE_DOC)
	{
		tok->content = ft_strdup("<<");
		tok->type = HERE_DOC;
	}
	if (!tok->content)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	tok = tok->next;
}

/* 
	we enter this function, if we are on a < or > character

	syntax should have been checked before, so we can assume, that there will
	be a file / limiter name after the redirection character

	function will implement that token, and return the position after the file

*/
static int	handle_redirection_type(t_msh *msh, char *pos, t_tok *new)
{
	if (*pos == '<')
	{
		if (*(pos + 1) == '<')
		{
			put_redi(msh, new, HERE_DOC);
			return (2);
		}
		put_redi(msh, new, REDI_IN);
		return (1);
	}
	else if (*pos == '>')
	{
		if (*(pos + 1) == '>')
		{
			put_redi(msh, new, REDI_AOUT);
			return (2);
		}
		put_redi(msh, new, REDI_TOUT);
		return (1);
	}
	return (0);
}

/* 
	we enter this function, if we are on a < or > character

	syntax should have been checked before, so we can assume, that there will
	be a file / limiter name after the redirection character

	function will implement that token, and return the position after the file
*/
char	*handle_redirection(t_msh *msh, char *pos)
{
	t_tok	*new;

	new = create_tok_node(msh);
	if (!new)
		return (NULL);
	add_tok_node(msh, new);
	pos += handle_redirection_type(msh, pos, new);
	return (pos);
}
