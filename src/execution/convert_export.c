/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:11:55 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/23 15:22:41 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	destroys the export safely
*/
void	destroy_exp(t_msh *msh)
{
	if (msh->export)
		destroy_str_array(msh->export);
	msh->export = NULL;
}

/*
	converts the environment list for export environment
*/
void	convert_exp(t_msh *msh)
{
	char	**env;
	t_env	*tmp;
	int		i;

	env = (char **)ft_calloc(msh->env_size + 1, sizeof(char *));
	if (!env)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	tmp = msh->env;
	if (msh->export)
		destroy_exp(msh);
	msh->export = env;
	i = 0;
	while (tmp)
	{
		if (!tmp->v_value)
		{
			env[i] = ft_strdup(tmp->v_name);
			tmp = tmp->next;
			i++;
			continue ;
		}
		env[i] = ft_strjoin_three(tmp->v_name, "=", tmp->v_value);
		if (!env[i])
			error_simple(msh, M_ERR, EXIT_FAILURE);
		tmp = tmp->next;
		i++;
	}
	msh->export = env;
}
