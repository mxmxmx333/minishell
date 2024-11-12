/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:55:52 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/12 12:17:58 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dont_needs_split(t_msh *msh, char *str)
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

int	get_level_1_len(t_msh *msh, t_tok *tok)
{
	int		len;
	char	*str;
	char	*start;

	len = 0;
	str = tok->content;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			start = str;
			str = ret_next_twin(str) + 1;
			len += str - start;
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

void	expand_vars(t_msh *msh, t_tok *tok, char *str)
{
	char	*expanded;
	char	*start;

	expanded = ft_calloc(get_level_1_len(msh, tok) + 1, sizeof(char));
	if (!expanded)
		return (error_simple(msh, M_ERR, 1));
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			start = str;
			str = ret_next_twin(str) + 1;
			ft_strncat(expanded, start, str - start);
		}
		else 
		{
			put_part_expander(msh, str, expanded);
			while (*str && *str != '\'' && *str != '\"')
				str++;
		}
	}
	free(tok->content);
	tok->content = expanded;
} 

void	token_add_back(t_tok **head, t_tok *new)
{
	t_tok	*current;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

char	*get_next_part(char *str)
{
	while (*str && !is_space(*str))
	{
		if (*str == '\'' || *str == '\"')
			str = ret_next_twin(str) + 1;
		else
			str++;
	}
	return (str);
}

t_tok	*new_token(t_tok *current, t_msh *msh, char *content, int type)
{
	t_tok	*new;

	if (!content)
		return (clear_tok_list(current), error_simple(msh, M_ERR, 1), NULL);
	new = ft_calloc(1, sizeof(t_tok));
	if (!new)
		return (free(content), clear_tok_list(current), 
				error_simple(msh, M_ERR, 1), NULL);
	new->content = content;
	new->type = type;
	return (new);
}

t_tok	*split_token(t_msh *msh, char *str)
{
	char	*start;
	t_tok	*current;
	char	*expanded;

	current = NULL;
	while (*str)
	{
		str = skip_whitespace(str);
		start = str;
		str = get_next_part(str);
		expanded = ft_strndup(start, str - start);
		if (!expanded)
			return (clear_tok_list(current), error_simple(msh, M_ERR, 1), NULL);
		expanded = expand(msh, expanded);
		if (!expanded)
			return (clear_tok_list(current), error_simple(msh, M_ERR, 1), NULL);
		token_add_back (&current, new_token(current, msh, expanded, WORD));
		if (str_is_empty(str))
			break ;
	}
	if (!current)
		return (new_token(current, msh, ft_strdup(""), WORD));
	return (current);
}

t_tok	*insert_new_tokens(t_msh *msh, t_tok *current, t_tok *tok)
{
	t_tok	*prev;
	t_tok	*next;

	if (msh->tokens == tok)
		prev = NULL;
	else
	{
		prev = msh->tokens;
		while (prev->next != tok)
			prev = prev->next;
	}
	next = tok->next;
	if (prev)
		prev->next = current;
	else
		msh->tokens = current;
	while (current && current->next)
		current = current->next;
	current->next = next;
	free(tok->content);
	free(tok);
	return (current);
}

void	cpy_varname(t_msh *msh, t_tok *tok, char *redirect)
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
		return (tok);
	}
	else
		cpy_varname(msh, tok, redirect);
	return (free(redirect), tok);
}

t_tok	*neo_expand(t_msh *msh, t_tok *tok)
{
	t_tok	*current;
	bool	lonely;

	if (tok->type == WORD)
	{
		if (!ft_strchr(tok->content, '\'') && !ft_strchr(tok->content, '\"'))
			lonely = true;
		else
			lonely = false;
		expand_vars(msh, tok, tok->content);
		current = split_token(msh, tok->content);
		current->lonely = lonely;
		return (insert_new_tokens(msh, current, tok));
	}
	if (tok->type == REDI_AOUT || tok->type == REDI_TOUT || tok->type == REDI_IN)
	{
		if (!ft_strchr(tok->file, '\'') && !ft_strchr(tok->file, '\"'))
			tok->lonely = true;
		expand_redirect(msh, tok);
		if (!str_is_empty(tok->file))
			tok->lonely = false;
	}
	if (tok->type == HERE_DOC)
		gen_here_doc(msh, tok);
	return (tok);
}
