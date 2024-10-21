/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:53:04 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/21 17:58:13 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_env(t_msh *msh, t_exec *exec)
{
	t_env	*temp;

	(void)exec;
	temp = msh->env;
	while (temp)
	{
		printf("%s=%s\n", temp->v_name, temp->v_value);
		temp = temp->next;
	}
	return (0);
}