/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:56:23 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/17 13:47:15 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_tokens(t_msh *msh)
{
	t_tok	*tmp;
	bool	pipe;
	t_tok	*redirections;
	t_exec	*exec_table;

	tmp = msh->tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD)
			process_cmd(msh, tmp);
		tmp = tmp->next;
	}
}
