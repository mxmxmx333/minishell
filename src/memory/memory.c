/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:42:01 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/18 18:07:07 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 	this function calls all the other destroy functions, and frees minishell, 
	to prepare a safe exit
*/
void	destroy_minishell(t_msh *msh)
{
	if (msh)
	{
		destroy_env(msh);
		destroy_exp(msh);
		ft_free((void **)&msh);
	}
}
