/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:09:15 by mbonengl          #+#    #+#             */
/*   Updated: 2024/08/08 14:17:09 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *str1, char const *str2)
{
	char	*joined;
	int		totallen;

	if (!str1 || !str2)
		return (NULL);
	totallen = ft_strlen(str1) + ft_strlen(str2) + 1;
	joined = ft_calloc(totallen, sizeof(char));
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, str1, totallen * sizeof(char));
	ft_strlcat(joined, str2, totallen * sizeof(char));
	return (joined);
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	int		len;
	char	*res;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	while (*s3)
		*res++ = *s3++;
	return (res - len);
}
