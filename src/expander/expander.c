/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:55:53 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/02 19:20:49 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*expand_quote(char *str)
{
	
} */

static int is_break(char c)
{
	return (c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '$');
}

char	*variable_finder(t_msh *msh, char *str)
{
	t_env	*env;
	char 	*start;

	if (*str != '$')
		return (error_complex(msh, ": is not a variable", str, 1), NULL);
	if (!*(str + 1) || is_break(*(str + 1)))
		return ("$");
	str++;
	start = str;
	while (*str && !is_break(*str))
		str++;
	env = msh->env;
	while (env)
	{
		if (!ft_strncmp(env->v_name, start, str - start))
			return (env->v_value);
		env = env->next;
	}
	return ("");
}

int	get_quote_len(t_msh *msh, char *str, char quote)
{
	int len;

	len = 0;
	if (quote == '\'')
	{
		while (*str && *str != quote)
		{
			str++;
			len++;
		}
		return (len);
	}
	while (*str && *str != quote)
	{
		if (*str == '$')
		{
			len += ft_strlen(variable_finder(msh, str));
			str++;
			while (*str && !is_break(*str))
				str++;
		}
		if (*str != quote && *str != '$')
		{
			str++;
			len++;
		}
	}
	return (len);
}

int	get_part_len(t_msh *msh, char *str)
{
	int len;

	len = 0;
	while (*str && *str != '\'' && *str != '\"')
	{
		if (*str == '$')
		{
			len += ft_strlen(variable_finder(msh, str));
			str++;
			while (*str && !is_break(*str))
				str++;
		}
		else if (*str != '\'' && *str != '\"' && *str != '$')
		{
			str++;
			len++;
		}
	}
	return (len);
}

int	get_expander_len(t_msh *msh, char *str)
{
	int len;

	len = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			len += get_quote_len(msh, str + 1, *str);
			str = ret_next_twin(str);
			str++;
		}
		else 
		{
			len += get_part_len(msh, str);
			while (*str && *str != '\'' && *str != '\"')
				str++;
		}
	}
	return (len);
}

char	*expand(t_msh *msh, t_tok *tok, char *str)
{
	(void)tok;
	printf("Expanding: %s\nStrlen for expanded String: %d\n", str, get_expander_len(msh, str));
	return (NULL);
}
