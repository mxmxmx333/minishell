/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:11:55 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/18 17:57:20 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*destroys the export environment memory, seg-fault, double free safe*/
void	destroy_exp(t_msh *msh)
{
	int	i;

	i = -1;
	if (msh->exp)
	{
		while (msh->exp[++i])
			ft_free((void **)&msh->exp[i]);
		ft_free((void **)&msh->exp);
	}
}

/*converts the environment list for export environment*/
void	convert_exp(t_msh *msh)
{
	char	**env;
	t_env	*tmp;
	int		i;

	env = (char **)ft_calloc(msh->env_size + 1, sizeof(char *));
	if (!env)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	tmp = msh->env;
	msh->exp = env;
	i = 0;
	while (tmp)
	{
		env[i] = ft_strjoin_three(tmp->v_name, "=", tmp->v_value);
		if (!env[i])
			error_simple(msh, M_ERR, EXIT_FAILURE);
		tmp = tmp->next;
		i++;
	}
	msh->exp = env;
}
