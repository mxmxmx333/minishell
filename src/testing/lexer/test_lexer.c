/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:33:45 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/27 15:20:30 by mbonengl         ###   ########.fr       */
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

void	test_lexer(t_msh *msh, char *argv)
{
	t_tok	*tok;
	
	msh->cur_cmd_line = ft_strdup(argv);
	if (!msh->cur_cmd_line)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	lexer(msh);
	free(msh->cur_cmd_line);
	tok = msh->tokens;
	int i = 0;
	while (tok)
	{
		printf("Tokennumber: %i\nToken: %s\nType: %s\nFile: %s\nExpand: %i\n\n",i,  tok->content, ret_type(tok), tok->file, tok->expand);
		tok = tok->next;
		i++;
	}
}