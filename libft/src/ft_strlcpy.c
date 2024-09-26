/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:17:35 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 19:08:03 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	index;

	index = 0;
	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	while (index + 1 < size && src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
	}
	if (size != 0)
		dst[index] = '\0';
	return (srclen);
}
