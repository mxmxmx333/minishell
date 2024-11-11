/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:55:52 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/11 13:30:50 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			len = str - start;
		}
		else
		{
			len = get_part_len(msh, str);
			while (*str && *str != '\'' && *str != '\"')
				str++;
		}
	}
	return (len);
}

void	expand_level_1(t_msh *msh, t_tok *tok, char *str)
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
	return (current);
}

void	expand_level_2(t_msh *msh, t_tok *current, t_tok *tok)
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
	while (current->next)
		current = current->next;
	current->next = next;
	free(tok->content);
	free(tok);
}

void	neo_expand(t_msh *msh, t_tok *tok)
{
	t_tok	*current;

	if (tok->type == WORD)
	{
		expand_level_1(msh, tok, tok->content);
		current = split_token(msh, tok->content);
		expand_level_2(msh, current, tok);
	}
}
