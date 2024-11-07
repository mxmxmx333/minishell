/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:44:38 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/07 14:29:14 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_here_doc(t_msh *msh)
{
	t_hdoc	*tmp;

	while (msh->here_doc)
	{
		tmp = msh->here_doc;
		msh->here_doc = msh->here_doc->next;
		if (tmp->file)
		{
			unlink(tmp->file);
			free(tmp->file);
		}
		free(tmp);
	}
	msh->here_doc = NULL;
}

void	add_here_doc(t_msh *msh, char *file)
{
	t_hdoc	*new;
	t_hdoc	*tmp;

	new = (t_hdoc *)ft_calloc(sizeof(t_hdoc), 1);
	if (!new)
		error_simple(msh, M_ERR, 1);
	new->file = ft_strdup(file);
	if (!new->file)
		error_simple(msh, M_ERR, 1);
	if (!msh->here_doc)
		msh->here_doc = new;
	else
	{
		tmp = msh->here_doc;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*trim_quotes(char *str, t_tok *curr)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char *)ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new[j++] = str[i];
			curr->expander = 1;
		}
		i++;
	}
	return (new);
}
