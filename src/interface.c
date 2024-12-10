/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:36:33 by mbonengl          #+#    #+#             */
/*   Updated: 2024/12/10 16:28:48 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	msh->last_exit = msh->status;
	msh->status = lexer(msh);
	signal(SIGINT, handle_sigint);
	if (msh->status)
		return (destroy_tokens(msh), destroy_here_doc(msh));
	parse_tokens(msh);
	execution(msh);
	destroy_here_doc(msh);
}

void	minishell_interface(t_msh *msh)
{
	while (1)
	{
		msh->cur_cmd_line = readline(msh->prompt);
		if (msh->cur_cmd_line == NULL)
			break ;
		else if (msh->cur_cmd_line && !str_is_empty(msh->cur_cmd_line))
		{
			minishell_interaction(msh);
			if (DISABLE_HISTORY)
				history_update(msh);
			free(msh->cur_cmd_line);
		}
	}
}
