/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_env_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */

/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:07:25 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/25 16:38:24 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_environment_list(t_msh *msh)
{
	t_env	*env;
	int		i = 0;

	env = msh->env;
	while (env)
	{
		printf("%d: %s=%s\n", i, env->v_name, env->v_value);
		env = env->next;
		i++;
	}
	printf("Number of environment variables: %zu\n", msh->env_size);
}
