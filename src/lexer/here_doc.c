/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:44:38 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/19 12:02:59 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_sig = 0;

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
	static int	i = 0;

	while (1)
	{
		i++;
		line = readline("> ");
		if (!tok->expander)
		{
			if (line)
				line = expand_heredoc(msh, line);
		}
		if (g_sig == 1)
			break ;
		if (!line || !ft_strcmp(line, limiter))
		{
			if (line)
				free(line);
			else
				here_doc_error(i, limiter);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

void	gen_here_doc(t_msh *msh, t_tok *tok)
{
	int		fd;
	char	*limiter;
	int		newfd;

	g_sig = 0;
	signal(SIGINT, handle_sigint_heredoc);
	newfd = wrapper_dup(STDIN_FILENO);
	limiter = gen_filename_heredoc(msh, tok);
	fd = open(tok->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (error_simple(msh, FD_ERR, 1));
	write_here_doc(msh, tok, limiter, fd);
	wrppd_dup2(msh, newfd, STDIN_FILENO);
	close(newfd);
	free(limiter);
	add_here_doc(msh, tok->file);
	close(fd);
	signal(SIGINT, handle_sigint);
}
