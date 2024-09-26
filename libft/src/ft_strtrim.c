/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:49:43 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 19:08:03 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	iscontained(char const c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	getstart(char const *str, char const *set)
{
	int	index;

	index = 0;
	while (str[index] && iscontained(str[index], set))
		index++;
	return (index);
}

int	getend(char const *str, char const *set)
{
	int	index;

	index = ft_strlen(str);
	while ((index && iscontained(str[index], set)) || str[index] == 0)
		index--;
	return (index + 1);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*trimmed;
	int		totallen;
	int		start;
	int		end;

	if (!str || !set)
		return (NULL);
	start = getstart(str, set);
	end = getend(str, set);
	totallen = end - start + 1;
	if (totallen < 1)
		totallen = 1;
	trimmed = (char *)ft_calloc(totallen, sizeof(char));
	if (!trimmed)
		return (NULL);
	if (totallen == 1)
	{
		*trimmed = '\0';
		return (trimmed);
	}
	ft_strlcpy(trimmed, str + start, totallen);
	return (trimmed);
}
