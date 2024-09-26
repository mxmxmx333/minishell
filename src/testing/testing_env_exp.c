/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_env_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */

/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:40:44 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/19 12:37:27 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_environment_exp(t_msh *msh)
{
	char	**exp;
	int		i = 0;

	exp = msh->export;
	while (exp[i])
	{
		printf("%d: %s\n", i, exp[i]);
		i++;
	}
	printf("Number of exported variables: %d\n", i);
	printf("Number of environment variables: %zu\n", msh->env_size);
}
