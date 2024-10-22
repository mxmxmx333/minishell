/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:32:11 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/22 13:23:12 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

//FIXME: remove this function in the end
void	print_tokens(t_msh *msh)
{
	t_tok	*token;
	int		i;

	if (!msh->tokens)
		return ;
	i = 0;
	token = msh->tokens;
	while (token)
	{
		printf("  Token:-------------:\n");
		printf("     NR: %d\n", i++);
		printf("   type: %s\n", get_type(token->type));
		printf(" string: %s\n", token->content);
		printf("splitme: %d\n", token->splitme);
		printf("   file: %s\n\n", token->file);
		token = token->next;
	}
}



//FIXME: remove this function in the end
void	print_token(t_tok *token)
{
	printf("  Token:-------------:\n");
	printf("   type: %s\n", get_type(token->type));
	printf(" string: %s\n", token->content);
	printf("splitme: %d\n", token->splitme);
	printf("   file: %s\n\n", token->file);
}

//FIXME: remove this function in the end
void	print_words_and_rest(t_msh *msh)
{
	t_tok *tmp;

	tmp = msh->words;
	printf("Words:--------------------------------------\n");
	while (tmp)
	{
		print_token(tmp);
		tmp = tmp->next;
	}
	tmp = msh->rest;
	printf("Rest:---------------------------------------\n");
	while (tmp)
	{
		print_token(tmp);
		tmp = tmp->next;
	}
}

void	print_executable(t_msh* msh)
{
	t_exec	*tmp;
	int		i;

	
	tmp = msh->exec_table;
	while (tmp)
	{
		i = -1;
		printf("Executable:----------------------------------\n");
		printf("    CMD: %s\n", tmp->cmd);
		//printf("Builtin: %s\n", tmp->builtin);
		printf("   Args: ");
		while (tmp->args[++i])
			printf("   Arg %i:%s ", i, tmp->args[i]);
		printf("\n");
		printf("  Redirections:-------------------- ");
		while (tmp->redirections)
		{
			printf("Type: %s\n", get_type(tmp->redirections->type));
			printf("File: %s\n", tmp->redirections->file);
			tmp->redirections = tmp->redirections->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
}
