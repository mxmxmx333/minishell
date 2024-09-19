/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:24:37 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/19 12:32:00 by mbonengl         ###   ########.fr       */
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
	test_environment_list(msh);
	prepare_execution(msh);
	test_environment_exp(msh);
	test_exec_paths(msh);
	(void)ac;
	(void)av;
	exit_success(msh);
	return (EXIT_SUCCESS);
}
