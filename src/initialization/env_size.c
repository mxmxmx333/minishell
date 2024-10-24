/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:27:27 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/24 13:55:58 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_size(t_msh *msh)
{
	t_env	*env;
	size_t	i;

	i = 0;
	env = msh->env;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
