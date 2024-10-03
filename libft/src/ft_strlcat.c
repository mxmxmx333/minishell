/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:29:53 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/03 16:18:29 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	idst;
	size_t	isrc;

	idst = 0;
	isrc = 0;
	while (idst < size && dst[idst])
		idst++;
	while (isrc + idst + 1 < size && src[isrc])
	{
		dst[idst + isrc] = src[isrc];
		isrc++;
	}
	if (idst != size)
		dst[idst + isrc] = '\0';
	return (idst + ft_strlen(src));
}

/* 
	Unsafe strncat function, only use when you are sure that 
	the destination string has enough space to hold the source string
*/
int	ft_strncat(char *dst, const char *src, int n)
{
	while (*dst)
		dst++;
	while (*src && n--)
		*dst++ = *src++;
	*dst = '\0';
	return (0);
}
