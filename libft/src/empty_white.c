/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_white.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:59:55 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/11 13:21:53 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	c_is_white(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' \
	|| c == '\r');
}

int	str_is_empty(char *str)
{
	while (*str)
	{
		if (!c_is_white(*str))
			return (0);
		str++;
	}
	return (1);
}

int	is_space(char c)
{
	return (c == ' ');
}
