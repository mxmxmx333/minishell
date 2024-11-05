/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:09:51 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/05 19:27:08 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_variable_finder(t_msh *msh, char *node)
{
	t_env	*tmp;

	tmp = msh->env;
	while (tmp)
	{
		if (!ft_strnrealcmp(tmp->v_name, node, ft_strlen(node)))
			return (tmp->v_value);
		tmp = tmp->next;
	}
	return (NULL);
}
