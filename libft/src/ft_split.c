/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:31:29 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 19:08:03 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wordcount(char const *s, char c)
{
	int	number;
	int	x;

	x = 0;
	number = 0;
	while (s[x])
	{
		while (s[x] == c)
			x++;
		if (s[x])
			number++;
		while (s[x] != c && s[x])
			x++;
	}
	return (number);
}

char	**freearr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**split_words(char const *s, char c, char **split)
{
	int		length;
	int		x;
	int		y;

	length = 0;
	x = 0;
	y = 0;
	while (s[y])
	{
		while (s[y] == c)
			y++;
		if (!s[y])
			break ;
		while (s[y] != c && s[y])
		{
			length++;
			y++;
		}
		split[x] = ft_substr(s, y - length, length);
		if (!split[x])
			return (freearr(split));
		x++;
		length = 0;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (0);
	split = (char **)ft_calloc(wordcount(s, c) + 1, sizeof(char *));
	if (!split)
		return (0);
	split = split_words(s, c, split);
	return (split);
}
