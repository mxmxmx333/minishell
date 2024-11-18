/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:34:04 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/18 09:44:14 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*create_executable(t_msh *msh)
{
	t_exec	*new;

	new = ft_calloc(sizeof(t_exec), 1);
	if (!new)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	return (new);
}

int	put_words(t_msh *msh, char **args, t_tok *words, size_t i)
{
	args[i] = ft_strdup(words->content);
	if (!args[i])
		error_simple(msh, M_ERR, EXIT_FAILURE);
	return (1);
}

int	get_args_size(t_tok *words)
{
	int		count;

	count = 0;
	while (words)
	{
		count++;
		words = words->next;
	}
	return (count);
}
