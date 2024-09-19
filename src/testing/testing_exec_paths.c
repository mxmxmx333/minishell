/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_exec_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:18:45 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/19 12:37:43 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_exec_paths(t_msh *msh)
{
	char	**paths;
	int		i = 0;

	paths = msh->paths;
	while (paths[i])
	{
		printf("%d: %s\n", i, paths[i]);
		i++;
	}
	printf("Number of paths: %d\n", i);
}
