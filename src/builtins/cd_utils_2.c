/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:09:51 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/14 15:04:06 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	swap_pwd(t_msh *msh)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	oldpwd = env_node_finder(msh, "OLDPWD");
	pwd = env_node_finder(msh, "PWD");
	if (!pwd)
		return (1);
	tmp = pwd->v_value;
	pwd->v_value = oldpwd->v_value;
	oldpwd->v_value = tmp;
	return (0);
}