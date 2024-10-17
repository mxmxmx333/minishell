/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:58:43 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/17 13:46:15 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	this function will control the lexer
	1. 	runs syntax checks. If there is an error, the program will exit.
		later on, error handling will be implemented.
	2. 	iterates over the command line and put the tokens into the list
	3. 	destroys the command line
*/
int	lexer(t_msh *msh)
{
	char	*position;

	if (check_syntax_error_quotes(msh))
		return (2);
	position = msh->cur_cmd_line;
	while (*position)
	{
		position = put_token_str(msh, position);
		if (!position)
			break ;
	}
	if (msh->tokens)
		if (refining_tokens(msh))
			return (2);
	return (0);
}

/*
	END,
	PIPE,
	REDI_IN,
	REDI_TOUT,
	REDI_AOUT,
	HERE_DOC,
	WORD,
	CMD,
	ARG
 */
char	*get_type(int type)
{
	if (type == NEWL)
		return ("NEWLINE");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDI_IN)
		return ("Input Redirection");
	if (type == REDI_TOUT)
		return ("Output Redirection Truncated");
	if (type == REDI_AOUT)
		return ("Output Redirection Appended");
	if (type == HERE_DOC)
		return ("Here_Doc");
	if (type == WORD)
		return ("WORD");
	if (type == CMD)
		return ("CMD");
	if (type == ARG)
		return ("ARG");
	return ("UNKNOWN");
}

void	print_tokens(t_msh *msh)
{
	t_tok	*token;
	int		i;

	i = 0;
	token = msh->tokens;
	while (token)
	{
		printf(" Token:-------------:\n");
		printf("    NR: %d\n", i++);
		printf("  type: %s\n", get_type(token->type));
		printf("string: %s\n", token->content);
		printf("  file: %s\n\n", token->file);
		token = token->next;
	}
}
