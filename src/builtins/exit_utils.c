/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:21:29 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/05 15:56:11 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checkoverflow(long long res, int num, int sign)
{
	if (sign == 1)
	{
		if (res > (LLONG_MAX - num) / 10)
			return (-300);
	}
	else
	{
		if (-res < (LLONG_MIN + num) / 10)
			return (-301);
	}
	return (1);
}

long long	ft_atoi_custom(const char *nptr)
{
	int			sign;
	long long	res;
	int			of;

	res = 0;
	sign = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9' && *nptr)
	{
		of = checkoverflow(res, *nptr - '0', sign);
		if (of != 1)
			return (of);
		res = res * 10 + *nptr - 48;
		nptr++;
	}
	return (res * sign);
}
