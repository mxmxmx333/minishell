/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:28 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/01 17:36:13 by mbonengl         ###   ########.fr       */
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
	
	msh = initialize_minishell(env);
	if (ac > 1)
		return (0);
	while (1)
	{
		msh->cur_cmd_line = readline(msh->prompt);
		test_lexer(msh, av[1]);
		destroy_tokens(msh);
	}
	return (exit_success(msh), EXIT_SUCCESS);
}
