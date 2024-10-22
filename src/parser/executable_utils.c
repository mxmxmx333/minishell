/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:34:04 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/22 13:22:53 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_executable(t_msh *msh)
{
	t_exec	*tmp;
	t_tok	*deleteme;

	while (msh->exec_table)
	{
		tmp = msh->exec_table;
		msh->exec_table = msh->exec_table->next;
		if (tmp->args)
			destroy_str_array(tmp->args);
		if (tmp->redirections)
		{
			while (tmp->redirections)
			{
				deleteme = tmp->redirections;
				tmp->redirections = tmp->redirections->next;
				destroy_tok_node(NULL, deleteme);
			}
		}
		if (tmp->cmd)
			free(tmp->cmd);
		//if (tmp->builtin)
		//	free(tmp->builtin);
		free(tmp);
	}
	msh->exec_table = NULL;
}

t_exec	*create_executable(t_msh *msh)
{
	t_exec	*new;

	new = ft_calloc(sizeof(t_exec), 1);
	if (!new)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	return (new);
}

static int	put_words2(t_msh *msh, char **args, t_tok *words, size_t i)
{
	args[i] = ft_strdup(words->content);
	if (!args[i])
		error_simple(msh, M_ERR, EXIT_FAILURE);
	return (1);
}

int	put_words(t_msh *msh, char **args, t_tok *words, size_t i)
{
	size_t	j;
	char	*str;
	int		start;

	start = i;
	str = words->content;
	if (words->splitme && !str_is_empty(words->content))
	{
		while (str)
		{
			j = 0;
			while (str[j] && !c_is_white(str[j]))
				++j;
			args[i] = ft_strndup(str, j);
			if (!args[i])
				error_simple(msh, M_ERR, EXIT_FAILURE);
			i++;
			str += j;
		}
	}
	else
		i += put_words2(msh, args, words, i);
	return (i - start);
}

int	get_args_size(t_tok *words)
{
	int		count;

	count = 0;
	while (words)
	{
		if (words->splitme)
			count += ft_countwords_whitespace(words->content);
		else
			count++;
		words = words->next;
	}
	return (count);
}
