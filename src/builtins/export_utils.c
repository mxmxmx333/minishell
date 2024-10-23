/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:59:34 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/23 14:19:13 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_two(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

static int	compare_strings(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] == s2[i])
		{
			i++;
			continue ;
		}
		else
			return (2);
	}
	return (0);
}

static int	is_sorted(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (compare_strings(env[i], env[i + 1]) == 1)
			return (-1);
	}
	return (1);
}

void	sort_export_array(t_msh *msh)
{
	char	**env;
	int		i;

	i = 0;
	env = msh->export;
	while (is_sorted(env) != 1)
	{
		if (env[i] == NULL)
			i = 0;
		if (compare_strings(env[i], env[i + 1]) == 1)
			swap_two(&env[i], &env[i + 1]);
		i++;
	}
}