/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:18:10 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/18 17:26:10 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long	get_seed(void)
{
	int				uninitialized_var;
	unsigned long	seed;

	seed = (unsigned long)&uninitialized_var;
	return (seed);
}

static unsigned long	get_random_number(unsigned long seed)
{
	seed = (seed * 1103515245 + 12345) & 0x7fffffff;
	return (seed);
}

static char	get_random_alphanum(unsigned long seed, int i)
{
	char			c;

	c = get_random_number((seed / (i * i + 1))) % 62;
	if (c < 10)
		return (c + '0');
	else if (c < 36)
		return (c - 10 + 'A');
	else
		return (c - 36 + 'a');
}

char	*gen_filename_heredoc(t_msh *msh, t_tok *tok)
{
	char	*filename;
	char	*limiter;
	char	*tmp;
	int		i;

	i = -1;
	limiter = tok->file;
	filename = ft_calloc(11, sizeof(char));
	if (!filename)
		return (error_simple(msh, M_ERR, 1), NULL);
	while (++i < 10)
		filename[i] = get_random_alphanum(get_seed(), i);
	tok->file = ft_strjoin("/tmp/here_doc_", filename);
	free(filename);
	if (!tok->file || !limiter)
		return (error_simple(msh, M_ERR, 1), NULL);
	tmp = limiter;
	limiter = trim_quotes(msh, limiter, tok);
	free(tmp);
	//tmp = limiter;
	//limiter = ft_strjoin(limiter, "\n");
	//free(tmp);
	return (limiter);
}
