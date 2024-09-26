/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:48:48 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 19:08:03 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		s_len;
	int		i;
	char	*array;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	array = ft_calloc(s_len + 1, sizeof(char));
	if (!array)
		return (0);
	while (s[i])
	{
		array[i] = f(i, s[i]);
		i++;
	}
	return (array);
}
