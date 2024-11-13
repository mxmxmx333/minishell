/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:55:52 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/13 20:37:35 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	needs_split(char *str)
{
	int	has_quote;
	int	has_var;

	has_quote = 0;
	has_var = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			str = ret_next_twin(str);
			has_quote++;
		}
		if (*str == '$')
			has_var++;
		str++;
	}
	if (has_var > 1 || (has_var && has_quote))
		return (1);
	return (0);
}

static t_tok	*expand_vars(t_msh *msh, t_tok *old, t_tok *replace)
{
	t_tok	*head;
	t_tok	*current;

	head = new_token(old, msh, ft_strdup(variable_finder_value(msh, replace->content)), 0);
	current = head;
	while (current && ft_countwords_whitespace(current->content) > 1)
	{
		split_expanded_variable(current);
		if (!current->next)
			return (clear_tok_list(head), clear_tok_list(old), error_simple(msh, M_ERR, 1), NULL);
		current = current->next;
	}
	return (insert_new_tokens(&old, head, replace));
}

static t_tok	*expand_and_split_vars(t_msh *msh, t_tok *tok)
{
	t_tok	*splitlist;
	t_tok	*tmp;

	splitlist = copy_token(msh, tok);
	tmp = splitlist;
	while (needs_split(tmp->content))
	{
		split_next_var(msh, splitlist, tmp);
		tmp = tmp->next;
	}
	tmp = splitlist;
	while (tmp)
	{
		if (tmp->expander)
			tmp = expand_vars(msh, splitlist, tmp);
		else
		{
			tmp->content = expand(msh, tmp->content);
			if (!tmp->content)
				return (clear_tok_list(splitlist), error_simple(msh, M_ERR, 1), NULL);
			tmp = tmp->next;
		}
	}
	return (manage_join(msh, splitlist));
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
		current = expand_and_split_vars(msh, tok);
		current->lonely = lonely;
		return (insert_new_tokens(&msh->tokens, current, tok));
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
