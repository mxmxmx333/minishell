/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:58:09 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 19:08:03 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;
	char	*src;

	little_len = ft_strlen(little);
	src = (char *)big;
	if (little_len == 0 || src == little)
		return (src);
	i = 0;
	while (i < len && src[i])
	{
		j = 0;
		while (little[j] == src[i + j] && little
			[j] && src[i + j] && i + j < len)
			j++;
		if (little[j] == '\0')
			return (src + i);
		i++;
	}
	return (NULL);
}
