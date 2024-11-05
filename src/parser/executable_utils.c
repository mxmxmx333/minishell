/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:34:04 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/05 13:47:04 by mbonengl         ###   ########.fr       */
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

static int	put_words2(t_msh *msh, char **args, t_tok *words, size_t i)
{
	if (str_is_empty(words->content) && words->splitme)
		return (0);
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
		while (*str)
		{
			j = 0;
			str = skip_whitespace(str);
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
