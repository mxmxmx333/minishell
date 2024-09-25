/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_path_finder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:45:30 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/25 16:47:46 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	will take av[0] as an arg (command) and will test the pathfinder with it

	tested inputs: (tested: 
	pathfinder return value, 
	exit status, 
	error handling, 
	leaks)
		- command (ls, echo, pwd, etc)
		- command with no permission
		- command, that is executable in only of the paths, but in others pem denied
		- non-existing command
		- empty string
		- absolute / relative path (not existing)
		- absolute / relative path (not executable)
		- absolute / relative path (is a directory)
		- absolute / relative path fine

	- NULL: pathfinder will print critical error message and exit
 */
void	test_pathfinder(t_msh *msh, char **av)
{
	int	i = 0;

	if (!av)
	{
		printf("No arguments provided\n");
		return ;
	}
	prepare_execution(msh);
	while (av[++i])
	{
		pathfinder(msh, av[i]);
		printf("%s: The path has been set to: %s\n", av[i], msh->exe_path);
		destroy_exe_path(msh);
	}
	pathfinder(msh, NULL);
	finished_execution(msh);	
}
