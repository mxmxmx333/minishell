/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:33:45 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/01 16:07:31 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_type(t_tok *tok)
{
	if (tok->type == END)
		return ("END");
	if (tok->type == PIPE)
		return ("PIPE");
	if (tok->type == REDI_IN)
		return ("REDI_IN");
	if (tok->type == REDI_TOUT)
		return ("REDI_TOUT");
	if (tok->type == REDI_AOUT)
		return ("REDI_AOUT");
	if (tok->type == HERE_DOC)
		return ("HERE_DOC");
	if (tok->type == WORD)
		return ("WORD");
	if (tok->type == CMD)
		return ("CMD");
	if (tok->type == ARG)
		return ("ARG");
	return ("UNKNOWN");
}

/* 

*/
void	test_lexer(t_msh *msh, char *argv)
{
	t_tok	*tok;

	msh->cur_cmd_line = ft_strdup(argv);
	if (!msh->cur_cmd_line)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	msh->status = lexer(msh);
	if (msh->status)
	{
		free(msh->cur_cmd_line);
		msh->cur_cmd_line = NULL;
		printf("Lexer returned with status: %i\n", msh->status);
		exit_success(msh);
	}
	printf("\nLexer returned with status: %i\n\n", msh->status);
	free(msh->cur_cmd_line);
	tok = msh->tokens;
	int i = 0;
	while (tok)
	{
		printf("Tokennumber: %i\nToken: %s\nType: %s\nFile: %s\nExpand: %i\
		\n----------------\n",i,  tok->content, ret_type(tok), tok->file, tok->expand);
		tok = tok->next;
		i++;
	}
}
