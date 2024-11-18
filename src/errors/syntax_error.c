/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/13 15:05:58 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_error_quotes(t_msh *msh)
{
	char	*temp;
	char	*err;

	temp = msh->cur_cmd_line;
	if (!temp)
		return (error_simple(msh, SUFA_ERR_SYX_Q_ERR, 42), 42);
	while (*temp)
	{
		if (*temp == '\"' || *temp == '\'')
		{
			err = temp;
			temp = ret_next_twin(temp);
			if (!*temp)
			{
				if (*err == '\"')
					return (display_tok_err(msh, SYN_QUO_ERR, "\"\n"), 2);
				if (*err == '\'')
					return (display_tok_err(msh, SYN_QUO_ERR, "\'\n"), 2);
			}
		}
		temp++;
	}
	return (0);
}

void	here_doc_error(int line, char *limiter)
{
	ft_putstr_fd("msh: warning: here-document at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	limiter[ft_strlen(limiter) - 1] = '\0'; 
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
}
