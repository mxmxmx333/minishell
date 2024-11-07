/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:47:45 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/07 15:42:33 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checkdivides(int n)
{
	int	count;

	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_itoa_custom(int n, char *array)
{
	int		i;

	i = checkdivides(n);
	i--;
	ft_bzero(array, 4);
	if (n == 0)
	{
		array[0] = '0';
		return ;
	}
	while (n)
	{
		array[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
}
/* 
	(c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '$' || \
		c == '/' || c == '.')
*/
int	is_varname_break(char c)
{
	return (c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '$' || \
			 c == '/' || c == '.');
}

int	ft_strnrealcmp(char *s1, char *s2, int n)
{
	if (!s1 || !s2)
		return (1);
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
	if (*start == '?')
	{
		ft_itoa_custom(msh->status, msh->status_char);
		return (msh->status_char);
	}
	env = msh->env;
	while (env)
	{
		if (!ft_strnrealcmp(env->v_name, start, str - start))
			return (env->v_value);
		env = env->next;
	}
	return ("");
}
