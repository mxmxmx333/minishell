/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/27 13:57:46 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	This function will check the command line for quotes. 
	
	o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o
	
	If a quote was not closed, it will display an error message 
	and exit the program.

	o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o
	
	This function has been tested, and it works as expected.

*/
int	check_syntax_error_quotes(t_msh *msh)
{
	char	*temp;
	char	*err;

	temp = msh->cur_cmd_line;
	if (!temp)
		return (error_simple(msh, SUFA_ERR_SYX_Q_ERR, 42), 42);
	while (*temp)
	{
		if (*temp == '\"' || *temp == '\'')
		{
			err = temp;
			temp = ret_next_twin(temp);
			if (!*temp)
			{
				if (*err == '\"')
					return (msh_error(msh, "\"\n", SYN_QUO_ERR, 2));
				if (*err == '\'')
					return (msh_error(msh, "\'\n", SYN_QUO_ERR, 2));
			}
		}
		temp++;
	}
	return (0);
}
