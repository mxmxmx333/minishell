/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:05:51 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 19:07:51 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*pointer;

	if (size && nmemb > SIZE_MAX / size)
		return (0);
	pointer = (void *)malloc(nmemb * size);
	if (!pointer)
		return (NULL);
	ft_bzero((void *)pointer, size * nmemb);
	return (pointer);
}
