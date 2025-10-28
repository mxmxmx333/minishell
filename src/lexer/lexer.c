/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:58:43 by mbonengl          #+#    #+#             */
/*   Updated: 2024/12/10 16:28:41 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	this function will control the lexer
	1. 	runs syntax checks. If there is an error it returns.
	2. 	iterates over the command line and put the tokens into the list
	3. 	destroys the command line
*/
int	lexer(t_msh *msh)
{
	char	*position;
	int		res;

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
	{
		res = refining_tokens(msh);
		if (res == 2)
			return (2);
		else if (res == 3)
			return (130);
	}
	if (msh->status == 42)
	{
		msh->status = 130;
		return (msh->status);
	}
	return (0);
}
