/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:58:43 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 18:58:47 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	this function will control the lexer, and put the tokens into the list
*/
void	lexer(t_msh *msh)
{
	char	*position;

	check_syntax_error_quotes(msh);
	position = msh->cur_cmd_line;
	while (*position)
	{
		position = put_token_str(msh, position);
		if (!position)
			break ;
	}
	destroy_cmd_line(msh);
}
