/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:58:43 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/27 15:18:06 by mbonengl         ###   ########.fr       */
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
void	lexer(t_msh *msh)
{
	char	*position;

	if (check_syntax_error_quotes(msh))
		return (destroy_cmd_line(msh));
	position = msh->cur_cmd_line;
	while (*position)
	{
		position = put_token_str(msh, position);
		if (!position)
			break ;
	}
	destroy_cmd_line(msh);
}
