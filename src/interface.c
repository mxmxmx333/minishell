/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:26:32 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/21 14:04:57 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// getting from main: 
/// cmd_line
///:Process Tokens
///:Print Tokens
///:Parse Tokens
///:Execute Execute:Table
///:Destroy History
///:Update History
///:Destroy cmd line
///:Destroy Tokens

/* 
**	This function is the interface of the minishell connecting the modules of 
**	the minishell project.
*/

static void	history_update(t_msh *msh)
{
	add_history(msh->cur_cmd_line);
	write_history_custom(msh, ".msh_history.txt", msh->cur_cmd_line);
	destroy_cmd_line(msh);
}

static void	minishell_interaction(t_msh *msh)
{
	msh->status = lexer(msh);
	printf("Lexer exited with status: %d\n", msh->status);
	print_tokens(msh);
	destroy_tokens(msh);
}

void	minishell_interface(t_msh *msh)
{
	while (1)
	{
		msh->cur_cmd_line = readline(msh->prompt);
		if (msh->cur_cmd_line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (msh->cur_cmd_line)
			minishell_interaction(msh);
		if (msh->cur_cmd_line && msh->cur_cmd_line[0] != '\0')
			history_update(msh);
	}
}
