/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:28:31 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/19 13:51:07 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_success(t_msh *msh)
{
	int	temp;

	temp = msh->status;
	destroy_minishell(msh);
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	exit(temp);
}

int	main(int ac, char **av, char **env)
{
	t_msh	*msh;

	(void)ac;
	(void)av;
	if (ac > 1)
		return (0);
	msh = initialize_minishell(env);
	minishell_interface(msh);
	return (exit_success(msh), EXIT_SUCCESS);
}
