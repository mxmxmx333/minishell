/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:25:54 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/11 16:51:13 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_white(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ft_countwords_delim(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (words);
}

int	ft_countwords_whitespace(char const *s)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_is_white(s[i]) && !str_is_empty((char *) (s + i)))
		{
			words++;
			while (s[i] && !ft_is_white(s[i]))
				i++;
		}
		else
			i++;
	}
	return (words);
}

int	ft_isoneword_delim(char const *s, char c)
{
	int	i;

	i = -1;
	if (c == 0)
		return (ft_strlen(s));
	while (s[++i])
	{
		if (s[i] == c)
			return (0);
	}
	return (i);
}

int	ft_isoneword_whitespace(char const *s)
{
	int	i;

	i = -1;
	while (s[++i] && !ft_is_white(s[i]))
	{
		if (ft_is_white(s[i]))
			return (0);
	}
	return (i);
}
