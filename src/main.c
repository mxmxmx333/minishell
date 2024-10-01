/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:28 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/01 19:09:04 by nicvrlja         ###   ########.fr       */
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

	//(void)av;
	msh = initialize_minishell(env);
	if (ac > 1)
		return (0);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		ft_putstr_fd(GREEN, STDOUT_FILENO);
		msh->cur_cmd_line = readline(msh->prompt);
		ft_putstr_fd(RESET, STDOUT_FILENO);
		add_history(msh->cur_cmd_line);
		test_lexer(msh, av[1]);
		destroy_tokens(msh);
	}
	return (exit_success(msh), EXIT_SUCCESS);
}
