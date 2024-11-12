/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:42:57 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/12 10:47:04 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_word_list(t_msh *msh, t_exec *table)
{
	t_tok	*words;
	size_t	i;

	i = 0;
	words = msh->words;
	if (!words)
		return ;
	if (words->lonely && !words->next && str_is_empty(words->content))
		table->lonely = true;
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
	t_exec	*tmp;

	table = create_executable(msh);
	tmp = msh->exec_table;
	if (!msh->exec_table)
		msh->exec_table = table;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = table;
		table->prev = tmp;
	}
	table->redirections = msh->rest;
	msh->rest = NULL;
	convert_word_list(msh, table);
	destroy_word(msh);
}
