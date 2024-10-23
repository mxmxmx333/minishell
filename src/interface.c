/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:26:32 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/23 15:48:43 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// getting from main: 
/// cmd_line
///:>Process Tokens
///:>Print Tokens
///:>Parse Tokens
///:>Execute Execute:>Table
///:>Destroy History
///:>Update History
///:>Destroy cmd line
///:>Destroy Tokens

///TODO: I have to update the expander to handle the tokens correctly: 

/* 
**	This function is the interface of the minishell connecting the modules of 
**	the minishell project.
*/

static void	history_update(t_msh *msh)
{
	if (msh->cur_cmd_line[0])
	{
		add_history(msh->cur_cmd_line);
		write_history_custom(msh, ".msh_history.txt", msh->cur_cmd_line);
	}
	destroy_cmd_line(msh);
}

static void	minishell_interaction(t_msh *msh)
{
	msh->status = lexer(msh);
	printf("Lexer exited with status: %d\n", msh->status);
	print_tokens(msh);
	printf("\nParsing Tokens...\n");
	parse_tokens(msh);
	printf("Remaining Tokens:\n");
	print_tokens(msh);
	printf("Executable Table:\n");
	print_executable(msh);
	destroy_word_and_rest(msh);
	execution(msh);
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
		if (msh->cur_cmd_line && !str_is_empty(msh->cur_cmd_line))
			minishell_interaction(msh);
		if (msh->cur_cmd_line)
			history_update(msh);
	}
}
