/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:36:29 by mbonengl          #+#    #+#             */
/*   Updated: 2024/08/25 13:33:44 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	lstclear(t_list **b_list)
{
	t_list	*temp;

	if (!b_list)
		return ;
	while (*b_list)
	{
		temp = *b_list;
		*b_list = (*b_list)->next;
		if (temp->str)
		{
			free(temp->str);
			temp->str = NULL;
		}
		free(temp);
		temp = NULL;
	}
	*b_list = NULL;
}

void	setupnext(t_list **b_list, char *n_buff)
{
	t_list	*temp;

	while ((*b_list)->next)
	{
		temp = *b_list;
		*b_list = (*b_list)->next;
		free(temp->str);
		temp->str = NULL;
		free(temp);
		temp = NULL;
	}
	free((*b_list)->str);
	(*b_list)->str = n_buff;
	if ((*b_list)->str[0] == '\0')
		lstclear(b_list);
}

size_t	getlinelen(t_list *b_list)
{
	size_t	i;
	size_t	j;

	if (!b_list)
		return (0);
	i = 0;
	while (b_list)
	{
		j = 0;
		while (b_list->str[j])
		{
			if (b_list->str[j] == '\n')
				return (i + 1);
			i++;
			j++;
		}
		b_list = b_list->next;
	}
	return (i);
}

void	ft_lstadd_back_gnl(t_list **lst, char *buffer)
{
	t_list	*current;
	t_list	*new_node;

	current = *lst;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buffer);
		buffer = NULL;
		return (lstclear(lst));
	}
	new_node->str = buffer;
	new_node->next = NULL;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

int	no_nl(t_list *b_list)
{
	int	i;

	i = 0;
	if (b_list == NULL)
		return (1);
	while (b_list)
	{
		i = 0;
		while (b_list->str[i] && i < BUFFER_SIZE)
		{
			if (b_list->str[i] == '\n')
				return (0);
			i++;
		}
		b_list = b_list->next;
	}
	return (1);
}
