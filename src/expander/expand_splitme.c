/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_splitme.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:42:47 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/07 17:19:15 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	it will write a trimmed version of the variable value to the expanded string
*/
void	add_trimmed_var(char *exp, char *v_value)
{
	char *str;

	str = v_value;
	while (*exp)
		exp++;
	str = skip_whitespace(str);
	while (*str && !c_is_white(*str))
	{
		*exp = *str;
		exp++;
		str++;
		if (c_is_white(*str))
		{
			str = skip_whitespace(str);
			if (!str_is_empty(str))
			{
				*exp = ' ';
				exp++;
			}
		}
	}
}

/* 
	returns of length of the expanded string of the variable, which trimmed 
	not needed spaces
*/
int	splitme_len(char *str)
{
	int	len;

	len = 0;
	str = skip_whitespace(str);
	while (*str)
	{
		str++;
		len++;
		if (c_is_white(*str))
		{
			str = skip_whitespace(str);
			if (!str_is_empty(str))
				len++;
		}
	}
	return (len);
}
