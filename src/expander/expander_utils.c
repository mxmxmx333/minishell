/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:47:45 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/21 15:51:06 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_varname_break(char c)
{
	return (c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '$');
}

int	ft_strnrealcmp(char *s1, char *s2, int n)
{
	if (n != (int)ft_strlen(s1))
		return (1);
	while (*s1 && *s2 && n--)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}

char	*variable_finder_value(t_msh *msh, char *str)
{
	t_env	*env;
	char	*start;

	if (*str != '$')
		return (error_complex(msh, ": is not a variable", str, 1), NULL);
	if (!*(str + 1) || is_varname_break(*(str + 1)))
		return ("$");
	str++;
	start = str;
	while (*str && !is_varname_break(*str))
		str++;
	env = msh->env;
	while (env)
	{
		if (!ft_strnrealcmp(env->v_name, start, str - start))
			return (env->v_value);
		env = env->next;
	}
	return ("");
}
