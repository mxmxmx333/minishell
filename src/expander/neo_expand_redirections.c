/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_expand_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:44:58 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/15 11:19:08 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dont_needs_split(t_msh *msh, char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str = ret_next_twin(str);
		if (*str == '$')
		{
			if (ft_countwords_whitespace(variable_finder_value(msh, str)) > 1)
				return (str);
			else
			{
				while (*str && !is_varname_break(*str))
					str++;
			}
		}
		str++;
	}
	return (str);
}

static void	cpy_varname(t_msh *msh, t_tok *tok, char *redirect)
{
	char	*start;
	char	*file;

	file = tok->file;
	start = redirect;
	++redirect;
	while (*redirect && !is_varname_break(*redirect))
		redirect++;
	*redirect = '\0';
	tok->file = ft_strndup(start, redirect - start);
	if (!tok->file)
		error_simple(msh, M_ERR, 1);
	free(file);
	tok->splitfile = true;
}

t_tok	*expand_redirect(t_msh *msh, t_tok *tok)
{
	char	*redirect;
	char	*cpy;

	redirect = dont_needs_split(msh, tok->file);
	if (!*redirect)
	{
		cpy = ft_strdup(tok->file);
		if (!cpy)
			return (error_simple(msh, M_ERR, 1), NULL);
		tok->file = expand(msh, tok->file);
		if (!tok->file)
			return (free(cpy), error_simple(msh, M_ERR, 1), NULL);
		if (str_is_empty(tok->file) && tok->lonely)
			cpy_varname(msh, tok, cpy);
		free(cpy);
		return (tok);
	}
	else
		cpy_varname(msh, tok, redirect);
	return (free(redirect), tok);
}
