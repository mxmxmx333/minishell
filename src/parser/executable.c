/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:42:57 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/24 14:45:59 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_word_list(t_msh *msh, t_exec *table)
{
	t_tok	*words;
	size_t	i;

	i = 0;
	words = msh->words;
	table->args = ft_calloc(sizeof(char *), get_args_size(words) + 1);
	if (!table->args)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	while (words)
	{
		i += put_words(msh, table->args, words, i);
		words = words->next;
	}
}

void	add_exeutable(t_msh *msh)
{
	t_exec	*table;

	table = create_executable(msh);
	if (!msh->exec_table)
		msh->exec_table = table;
	else
	{
		while (msh->exec_table->next)
			msh->exec_table = msh->exec_table->next;
		msh->exec_table->next = table;
		table->prev = msh->exec_table;
	}
	table->redirections = msh->rest;
	msh->rest = NULL;
	convert_word_list(msh, table);
	destroy_word(msh);
}
