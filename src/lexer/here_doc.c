/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:44:38 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/18 13:42:44 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t g_sig = 0;

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

char	*trim_quotes(t_msh *msh, char *str, t_tok *curr)
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
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			curr->expander = 1;
		}
		else
			new[j++] = str[i++];
	}
	if (!curr->expander)
		new = expand(msh, new);
	return (new);
}

void	write_here_doc(t_msh *msh, t_tok *tok, char *limiter, int fd)
{
	char		*line;
	static int	i;
	int			status;
	int			newfd;

	i = 1;
	status = 0;
	g_sig = 0;
	newfd = wrapper_dup(msh);
	while (1)
	{
		get_status(&msh->status);
		signal(SIGINT, handle_sigint_heredoc);
		line = get_next_line(STDIN_FILENO, &status);
		if (!line && status == 1)
			break ;
		if (!line)
		{
			here_doc_error(i, limiter);
			break ;
		}
		if (!tok->expander)
			line = expand_heredoc(msh, line);
		if (!ft_strcmp(line, limiter))
		{
			if (line)
				free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		i++;
	}
	wrapper_dup2(msh, newfd, STDIN_FILENO);
	close(newfd);
}

void	gen_here_doc(t_msh *msh, t_tok *tok)
{
	int		fd;
	char 	*limiter;

	limiter = gen_filename_heredoc(msh, tok);
	fd = open(tok->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (error_simple(msh, FD_ERR, 1));
	write_here_doc(msh, tok, limiter, fd);
	free(limiter);
	add_here_doc(msh, tok->file);
	close(fd);
	signal(SIGINT, handle_sigint);
}
