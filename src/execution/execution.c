/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:07:10 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/19 12:31:06 by mbonengl         ###   ########.fr       */
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
