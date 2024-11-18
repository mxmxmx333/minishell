/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:36:33 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/18 09:14:43 by mbonengl         ###   ########.fr       */
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
	msh->status = lexer(msh);
	if (msh->status)
		return (destroy_tokens(msh), destroy_here_doc(msh));
	parse_tokens(msh);
	print_tokens(msh);
	execution(msh);
	destroy_here_doc(msh);
}

void	handle_piped_input(t_msh *msh)
{
	char	*line;
	char	*tmp;

	line = get_next_line(STDIN_FILENO);
	tmp = msh->cur_cmd_line;
	msh->cur_cmd_line = ft_strtrim(line, "\n");
	free(tmp);
	free(line);
}

void	minishell_interface(t_msh *msh)
{
	while (1)
	{
		if (isatty(STDIN_FILENO))
			msh->cur_cmd_line = readline("Msh->");
		else
			handle_piped_input(msh);
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
