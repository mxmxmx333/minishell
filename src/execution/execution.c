/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:55:24 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 18:55:29 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* exit point for the execution, destroys all the generated assets */
void	finished_execution(t_msh *msh)
{
	destroy_exp(msh);
	destroy_paths(msh);
}

/* entry point for the execution, generates the neccesairy assets */
void	prepare_execution(t_msh *msh)
{
	convert_exp(msh);
	extract_paths(msh);
}
