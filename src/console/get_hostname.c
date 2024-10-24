/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:58:08 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/24 14:55:51 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"

/*
	This function trims the hostname until the first dot
	It's mostly useful to make it look like in 42 School Computers.
*/
static char	*trim_hostname(char *str)
{
	int		i;
	char	*hostname;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	hostname = ft_calloc(i + 1, sizeof(char));
	if (!hostname)
		return (perror("malloc fail"), NULL);
	i = 0;
	while (str[i] && str[i] != '.')
	{
		hostname[i] = str[i];
		i++;
	}
	hostname[i] = '\0';
	return (hostname);
}

/*
	Function that retrieves the hostname for the prompt.
*/
char	*get_hostname(void)
{
	char	*hostname;
	char	*res;
	int		fd;
	int		i;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (perror("Failed to open hostname file."), NULL);
	res = NULL;
	hostname = NULL;
	i = 0;
	hostname = get_next_line(fd);
	if (!hostname)
		return (close(fd), close(fd), NULL);
	i = ft_strlen(hostname) - 1;
	hostname[i] = '\0';
	res = trim_hostname(hostname);
	free(hostname);
	close(fd);
	return (res);
}
