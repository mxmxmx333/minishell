/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/30 17:34:56 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	check_token_err_pipe(t_msh *msh)
{
	t_tok	*tok;

	tok = msh->tokens;
	while (tok)
	{
		if (tok->type == PIPE)
		{
			if (!tok->next)
				return (error_complex_tok(msh, "coming soon", SYN_ERR_UNEXP_TOK, 2), 2);
			else if (tok->next->type == PIPE)
				return (error_complex_tok(msh, "|", SYN_ERR_UNEXP_TOK, 2), 2);
		}
		tok = tok->next;
	}
} */

/* 
	This function will check the tokens for syntax errors,
	specificaly for redirections. 
	
	If a REDI_ is not followed by a WORD, it will display a 
	specific error message and exit the process.
*/
/* void	check_token_err_redi(t_msh *msh)
{
	t_tok	*tok;

	tok = msh->tokens;
	while (tok)
	{
		if (isredi(tok->type))
		{
			if (!tok->next)
				return (error_complex_tok(msh, "newline", SYN_ERR_UNEXP_TOK, 2));
			else if (tok->next->type != WORD)
				return (error_complex_tok(msh, tok->next->content, SYN_ERR_UNEXP_TOK, 2));
		}
		tok = tok->next;
	}
} */

/* 
	This function will check the command line for quotes. 
		
	If a quote was not closed, it will display an error message 
	and exit the program.
	
	This function has been tested, and it works as expected.
*/
void	check_syntax_error_quotes(t_msh *msh)
{
	char	*temp;
	char	*err;

	temp = msh->cur_cmd_line;
	if (!temp)
		return (error_simple(msh, SUFA_ERR_SYX_Q_ERR, 42));
	while (*temp)
	{
		if (*temp == '\"' || *temp == '\'')
		{
			err = temp;
			temp = ret_next_twin(temp);
			if (!*temp)
			{
				if (*err == '\"')
					return (error_complex(msh, SYN_QUO_ERR, "\"\n", 2));
				if (*err == '\'')
					return (error_complex(msh, SYN_QUO_ERR, "\'\n", 2));
			}
		}
		temp++;
	}
}
