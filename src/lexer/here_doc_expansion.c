/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:03:34 by mbonengl          #+#    #+#             */
/*   Updated: 2024/12/10 11:41:01 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_heredoc_exp_len(t_msh *msh, char *str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			len += ft_strlen(variable_finder_value(msh, &str[i]));
			i++;
			while (!is_varname_break(str[i]))
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static char	*expand_heredoc_work(t_msh *msh, char *str)
{
	char	*new;
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char *)ft_calloc(sizeof(char), get_heredoc_exp_len(msh, str) + 2);
	if (!new)
		return (error_simple(msh, M_ERR, 1), NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			var = variable_finder_value(msh, &str[i]);
			ft_strncat(new, var, ft_strlen(var));
			i++;
			while (!is_varname_break(str[i]))
				i++;
			j += ft_strlen(var);
		}
		else
			new[j++] = str[i++];
	}
	return (free(str), new);
}

char	*expand_heredoc(t_msh *msh, char *str, t_tok *tok)
{
	char	*expanded;
	char	*expanded_nl;

	if (tok->expander)
		return (append_nl(msh, str));
	expanded = expand_heredoc_work(msh, str);
	if (!expanded)
		return (error_simple(msh, M_ERR, 1), NULL);
	expanded_nl = ft_strjoin(expanded, "\n");
	free(expanded);
	if (!expanded_nl)
		return (error_simple(msh, M_ERR, 1), NULL);
	return (expanded_nl);
}
