/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 19:36:23 by mbonengl         ###   ########.fr       */
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
void	check_syntax_error_quotes(t_msh *msh)
{
	char	*temp;
	char	*err;

	temp = msh->cur_cmd_line;
	while (*temp)
	{
		if (*temp == '\"' || *temp == '\'')
		{
			err = temp;
			temp = ret_next_twin(temp);
			if (!*temp)
			{
				if (*err == '\"')
					return (error_complex(msh, "\"\n", SYN_QUO_ERR, 2));
				if (*err == '\'')
					return (error_complex(msh, "\'\n", SYN_QUO_ERR, 2));
			}
		}
		temp++;
	}
}
