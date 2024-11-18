/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:36:31 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/18 17:02:29 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	resetlist(t_list **b_list)
{
	t_list	*temp;
	size_t	start;
	size_t	i;
	char	*n_buff;

	if (no_nl(*b_list) || *b_list == NULL)
		return (lstclear(b_list));
	temp = *b_list;
	while (temp->next)
		temp = temp->next;
	start = getlinelen(temp);
	n_buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE - start) + 1);
	if (!n_buff)
		return (lstclear(b_list));
	i = 0;
	while (temp->str[start])
		n_buff[i++] = temp->str[start++];
	n_buff[i] = '\0';
	setupnext(b_list, n_buff);
}

char	*takeline(t_list *b_list)
{
	size_t	linelen;
	char	*str;
	int		x;
	int		y;

	linelen = getlinelen(b_list);
	if (linelen == 0)
		return (NULL);
	str = (char *)malloc(linelen + 1);
	if (!str)
		return (NULL);
	x = 0;
	while (b_list)
	{
		y = 0;
		while (b_list->str[y] && b_list->str[y] != '\n')
			str[x++] = b_list->str[y++];
		if (b_list->str[y] == '\n')
			break ;
		b_list = b_list->next;
	}
	if (b_list != NULL && b_list->str[y] == '\n')
		str[x++] = '\n';
	str[x] = '\0';
	return (str);
}

int	copycontent(int fd, t_list **b_list)
{
	char	*buffer;
	ssize_t	readsize;

	buffer = NULL;
	if (!no_nl(*b_list))
		return (1);
	while (no_nl(*b_list))
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (-1);
		readsize = read(fd, buffer, BUFFER_SIZE);
		if (readsize == 0)
		{
			free(buffer);
			buffer = NULL;
			return (1);
		}
		if (readsize < 0)
			return (free(buffer), -1);
		buffer[readsize] = '\0';
		ft_lstadd_back_gnl(b_list, buffer);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*b_list = NULL;
	char			*current_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (lstclear(&b_list), NULL);
	if (copycontent(fd, &b_list) == -1)
		return (lstclear(&b_list), NULL);
	if (!b_list)
		return (resetlist(&b_list), NULL);
	current_line = takeline(b_list);
	if (!current_line)
		return (lstclear(&b_list), NULL);
	resetlist(&b_list);
	return (current_line);
}
