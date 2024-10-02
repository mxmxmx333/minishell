/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:03:28 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/02 17:58:22 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"

/*
	Create the file name so that it includes the home directory
	Still need to free the memory!
*/
static char	*create_filename(t_msh *msh, char *filename)
{
	char	*res;
	char	*home;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	home = msh->home_dir;
	res = ft_strjoin(res, home);
	res = ft_strjoin(res, "/");
	res = ft_strjoin(res, filename);
	if (!res)
		return (NULL);
	return (res);
}

/*
	Open the .msh_history.txt file and write the command
	after that write the delimiter.
*/
int	write_history_custom(t_msh *msh, char *filename, char *line)
{
	int		fd;
	char	delim;
	char	*path;

	path = create_filename(msh, filename);
	fd = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRWXG | S_IRWXU);
	if (fd == -1)
		return (error_complex(msh, FD_ERR, path, EXIT_FAILURE), 0);
	delim = 3;
	ft_putstr_fd(line, fd);
	ft_putchar_fd(delim, fd);
	close(fd);
	return (1);
}

/*
	Reads the line until EOF and joins it together into a one single string.
*/
static char	*add_history_custom(t_msh *msh, char *filename)
{
	int		fd;
	char	*line;
	char	*history;
	char	*temp;
	char	*path;

	path = create_filename(msh, filename);
	fd = open(path, O_RDWR | O_CREAT, S_IRWXG | S_IRWXU);
	if (fd == -1)
		return (error_complex(msh, FD_ERR, path, EXIT_FAILURE), NULL);
	history = ft_strdup("");
	if (!history)
		return (error_simple(msh, M_ERR, EXIT_FAILURE), NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		temp = history;
		history = ft_strjoin(history, line);
		free(temp);
		free(line);
	}
	return (close(fd), history);
}

/*
	Split the joined string with ft_split and user add_history()
	to load the commands from the file to the program's memory.
*/
int	read_history_custom(t_msh *msh, char *filename)
{
	char	**splitted_history;
	char	*history;
	int		i;

	i = 0;
	history = add_history_custom(msh, filename);
	splitted_history = ft_split(history, 3);
	while (splitted_history[i])
	{
		add_history(splitted_history[i]);
		i++;
	}
	return (1);
}
