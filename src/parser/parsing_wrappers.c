/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wrappers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:34:39 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/05 17:36:27 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*wrpped_ft_strndup(t_msh *msh, char *str, int n)
{
	char	*new;

	new = ft_strndup(str, n);
	if (!new)
		error_simple(msh, M_ERR, EXIT_FAILURE);
	return (new);
}
