/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:55:30 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 19:08:03 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*alloc_zero(void)
{
	char	*ptr;

	ptr = (char *)ft_calloc(1, sizeof(char));
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	int		s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > (unsigned int)s_len)
		return (alloc_zero());
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substring = (char *)ft_calloc((len + 1), sizeof(char));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}
