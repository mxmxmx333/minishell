/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:55:44 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/16 16:12:42 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	returns the length of a string that is not a variable inside a 
	non quote part
*/
int	get_len_not_var_in_part(char *str)
{
	int	len;

	len = 0;
	while (*str && *str != '\'' && *str != '\"' && *str != '$')
	{
		str++;
		len++;
	}
	return (len);
}

/* 
	returns the length of a string that is not a variable inside a quote
*/
int	get_len_not_var_in_quote(char *str, char quote)
{
	int	len;

	len = 0;
	while (*str && *str != quote && *str != '$')
	{
		str++;
		len++;
	}
	return (len);
}

/* 
	returns the length of a single quoted string
*/
int	get_single_len(char *str)
{
	int	len;

	len = 0;
	while (*str && *str != '\'')
	{
		str++;
		len++;
	}
	return (len);
}

/* 
	returns the length for the the expanded quote
*/
int	get_quote_len(t_msh *msh, char *str, char quote)
{
	int	len;

	len = 0;
	if (quote == '\'')
		return (get_single_len(str));
	while (*str && *str != quote)
	{
		if (*str == '$')
		{
			len += ft_strlen(variable_finder_value(msh, str));
			str++;
			while (*str && !is_varname_break(*str))
				str++;
		}
		else
		{
			len += get_len_not_var_in_quote(str, quote);
			while (*str && *str != quote && *str != '$')
				str++;
		}
	}
	return (len);
}

/* 
	returns the length of the expanded part of the string that is not a quote
*/
int	get_part_len(t_msh *msh, char *str)
{
	int	len;

	len = 0;
	while (*str && *str != '\'' && *str != '\"')
	{
		if (*str == '$')
		{
			len += ft_strlen(variable_finder_value(msh, str));
			str++;
			while (*str && !is_varname_break(*str))
				str++;
		}
		else if (*str != '\'' && *str != '\"' && *str != '$')
		{
			str++;
			len++;
		}
	}
	return (len);
}
