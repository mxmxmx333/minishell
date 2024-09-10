/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:50:32 by mbonengl          #+#    #+#             */
/*   Updated: 2024/08/25 15:22:27 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checkdivides(int n)
{
	int	count;

	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*itoanegative(int n)
{
	char	*array;
	int		pos;

	pos = checkdivides(n);
	array = (char *)ft_calloc(pos + 2, sizeof(char));
	if (!array)
		return (NULL);
	if (n == -2147483648)
	{
		array[pos] = '8';
		n /= 10;
		pos--;
	}
	n = -n;
	while (n)
	{
		array[pos] = n % 10 + '0';
		n /= 10;
		pos--;
	}
	array[pos] = '-';
	return (array);
}

char	*itoazero(void)
{
	char	*array;

	array = (char *)ft_calloc(2, sizeof(char));
	if (!array)
		return (NULL);
	array[0] = '0';
	return (array);
}

char	*ft_itoa(int n)
{
	char	*array;
	int		pos;

	if (n < 0)
		return (itoanegative(n));
	if (n == 0)
		return (itoazero());
	pos = checkdivides(n);
	array = (char *)ft_calloc(pos + 1, sizeof(char));
	if (!array)
		return (NULL);
	while (n)
	{
		array[pos - 1] = n % 10 + '0';
		n /= 10;
		pos--;
	}
	return (array);
}
