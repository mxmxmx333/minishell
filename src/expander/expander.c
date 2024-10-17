/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:55:53 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/17 14:01:55 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	returns the length for the whole expanded string
*/
static int	get_expander_len(t_msh *msh, char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			len += get_quote_len(msh, str + 1, *str);
			str = ret_next_twin(str);
			str++;
		}
		else
		{
			len += get_part_len(msh, str);
			while (*str && *str != '\'' && *str != '\"')
				str++;
		}
	}
	return (len);
}

/*
	put the expanded part of the string that is a quote
*/
void	put_quote_expander(t_msh *msh, char *str, char *exp, char quote)
{
	if (quote == '\'')
	{
		ft_strncat(exp, str, get_single_len(str));
		return ;
	}
	else
	{
		while (*str && *str != quote)
		{
			if (*str == '$')
			{
				ft_strncat(exp, variable_finder_value(msh, str), \
							ft_strlen(variable_finder_value(msh, str)));
				str++;
				while (*str && !is_varname_break(*str))
					str++;
			}
			else
			{
				ft_strncat(exp, str, get_len_not_var_in_quote(str, quote));
				while (*str && *str != quote && *str != '$')
					str++;
			}
		}
	}
}

/* 
	put the expanded part of the string that is not a quote
*/
void	put_part_expander(t_msh *msh, char *str, char *exp)
{
	char	*v_value;
	int		len;

	while (*str && *str != '\'' && *str != '\"')
	{
		if (*str == '$')
		{
			v_value = variable_finder_value(msh, str);
			ft_strncat(exp, v_value, ft_strlen(v_value));
			str++;
			while (*str && !is_varname_break(*str))
				str++;
		}
		else
		{
			len = get_len_not_var_in_part(str);
			ft_strncat(exp, str, len);
			str += len;
		}
	}
}

static void	put_expanded(t_msh *msh, char *str, char *exp)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			put_quote_expander(msh, str + 1, exp, *str);
			str = ret_next_twin(str);
			str++;
		}
		else
		{
			put_part_expander(msh, str, exp);
			while (*str && *str != '\'' && *str != '\"')
				str++;
		}
	}
}

char	*expand(t_msh *msh, char *str)
{
	int		len;
	char	*exp;

	len = get_expander_len(msh, str);
	if (!len)
		return (ft_strdup(""));
	exp = (char *)ft_calloc(sizeof(char), len + 1);
	if (!exp)
		return (error_simple(msh, M_ERR, 1), NULL);
	put_expanded(msh, str, exp);
	free(str);
	return (exp);
}
