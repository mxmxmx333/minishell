/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:29:53 by mbonengl          #+#    #+#             */
/*   Updated: 2024/04/19 17:12:04 by mbonengl         ###   ########.fr       */
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
