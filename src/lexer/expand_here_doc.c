/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:31:32 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/07 14:41:48 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_expander_len(t_msh *msh, char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			len++;
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

static void	put_expanded(t_msh *msh, char *str, char *exp)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (*str == '\'')
				ft_strcat(exp, "'");
			else
				ft_strcat(exp, "\"");
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

char	*expand_heredoc(t_msh *msh, char *str)
{
	int		len;
	char	*exp;

	len = get_expander_len(msh, str);
	if (!len)
	{
		if (str)
			free(str);
		return (ft_strdup(""));
	}
	exp = (char *)ft_calloc(sizeof(char), len + 1);
	if (!exp)
		return (error_simple(msh, M_ERR, 1), NULL);
	put_expanded(msh, str, exp);
	free(str);
	return (exp);
}
