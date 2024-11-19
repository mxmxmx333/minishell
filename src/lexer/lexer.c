/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:58:43 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/19 11:27:39 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	this function will control the lexer
	1. 	runs syntax checks. If there is an error, the program will exit.
		later on, error handling will be implemented.
	2. 	iterates over the command line and put the tokens into the list
	3. 	destroys the command line
*/
int	lexer(t_msh *msh)
{
	char	*position;

	if (check_syntax_error_quotes(msh))
		return (2);
	position = msh->cur_cmd_line;
	while (*position)
	{
		position = put_token_str(msh, position);
		if (!position)
			break ;
	}
	if (msh->tokens)
		if (refining_tokens(msh))
			return (2);
	if (msh->status == 42)
	{
		msh->status = 130;
		return (msh->status);
	}
	return (0);
}
