/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:28 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 18:55:02 by mbonengl         ###   ########.fr       */
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
	{
		msh->cur_cmd_line = ft_strdup(av[1]);
		check_syntax_error_quotes(msh);
		printf("cmd_line: %s\n syntax correct :) \n", msh->cur_cmd_line);
	}
	return (exit_success(msh), EXIT_SUCCESS);
}
