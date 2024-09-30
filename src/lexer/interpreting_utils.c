/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:49:02 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/30 12:03:35 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* 
	Utility function to check if a token is a redirection token.
*/
int	isredi(int type)
{
	return (type == REDI_IN || type == REDI_TOUT ||
			type == REDI_AOUT || type == HERE_DOC);
}

/* 
	This function will return true, if the character is a token end, and false
	if it is not. 

	c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' \
	|| c == '\r' || c == '|' || c == '<' || c == '>' || c == 0
*/
int	is_end_token(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' \
	|| c == '\r' || c == '|' || c == '<' || c == '>' || c == 0)
		return (1);
	return (0);
}

/* 
	This function will return true if the character is a redirection character:
	'<' or '>'.
*/
int	is_redirection(char c)
{
	return (c == '<' || c == '>');
}
/* 
	This function will return the pointer to the next char in the string, 
	that is identical with the first character in the string.
	If it fails, it will return pointer to the null terminator.
	Useful, to close the quotes.
*/
char	*ret_next_twin(char *position)
{
	char	quote;

	quote = *position;
	while (*position)
	{
		position++;
		if (*position == quote)
			return (position);
	}
	return (position);
}

/* 
	This function will skip the white spaces in the string, and return the
	pointer to the first non white space character.
*/
char	*skip_whitespace(char *position)
{
	while (c_is_white(*position))
		position++;
	return (position);
}