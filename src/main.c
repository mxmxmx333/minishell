/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:28 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/03 17:59:52 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_success(t_msh *msh)
{
	destroy_minishell(msh);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_msh	*msh;

	(void)ac;
	(void)av;
	msh = initialize_minishell(env);
	if (ac > 1)
		return (0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	read_history_custom(msh, ".msh_history.txt");
	while (1)
	{
		msh->cur_cmd_line = readline(msh->prompt);
		if (msh->cur_cmd_line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (msh->cur_cmd_line && msh->cur_cmd_line[0] != '\0')
		{
			add_history(msh->cur_cmd_line);
			write_history_custom(msh, ".msh_history.txt", msh->cur_cmd_line);
		}
		if (msh->cur_cmd_line)
		{
			test_lexer(msh, av[0]);
			destroy_tokens(msh);
		}
	}
	return (exit_success(msh), EXIT_SUCCESS);
}
