/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:39:20 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 18:06:46 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "minishell.h"

/*-----------------------------> cleaning memory <----------------------------*/

void	destroy_minishell(t_msh *msh);
void	destroy_str_array(char **str);
void	destroy_cmd_line(t_msh *msh);

#endif