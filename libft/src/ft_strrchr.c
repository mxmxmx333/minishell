/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:26:55 by mbonengl          #+#    #+#             */
/*   Updated: 2024/04/19 16:49:08 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	while (*s != (char)c && i != 0)
	{
		s--;
		i--;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
