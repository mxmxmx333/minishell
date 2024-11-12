/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:36:33 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/12 13:59:18 by mbonengl         ###   ########.fr       */
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
	if (msh->status)
		return (destroy_here_doc(msh));
	// printf("Lexer exited with status: %d\n", msh->status);
	// print_tokens(msh);
	// printf("\nParsing Tokens...\n");
	parse_tokens(msh);
	// printf("Remaining Tokens:\n");
	print_tokens(msh);
	// printf("Executable Table:\n");
	// print_executable(msh);
	execution(msh);
	destroy_here_doc(msh);
	// printf("Exit status:%d\n", msh->status);
}

void	minishell_interface(t_msh *msh)
{
	while (1)
	{
		if (isatty(STDIN_FILENO))
			msh->cur_cmd_line = readline("Msh->");
		else
		{
			char	*line;
			char	*tmp;
			line = get_next_line(STDIN_FILENO);
			tmp = msh->cur_cmd_line;
			msh->cur_cmd_line = ft_strtrim(line, "\n");
			free(tmp);
			free(line);
		}
		if (msh->cur_cmd_line == NULL)	
		{
			//printf("exit\n");
			break ;
		}
		else if (msh->cur_cmd_line && !str_is_empty(msh->cur_cmd_line))
		{
			minishell_interaction(msh);
			if (DISABLE_HISTORY)
				history_update(msh);
			free(msh->cur_cmd_line);
		}	
	}
}
