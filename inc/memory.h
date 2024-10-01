/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:39:20 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/01 20:01:14 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "minishell.h"

/*-----------------------------> cleaning memory <----------------------------*/

void	destroy_minishell(t_msh *msh);
void	destroy_str_array(char **str);
void	destroy_cmd_line(t_msh *msh);
void	destroy_prompt(t_msh *msh);

#endif