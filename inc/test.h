/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */

/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:05:02 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/25 16:45:09 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "minishell.h"

void	test_environment_list(t_msh *msh);
void	test_environment_exp(t_msh *msh);
void	test_paths(t_msh *msh);
void	test_pathfinder(t_msh *msh, char **av);
void	test_lexer(t_msh *msh, char *argv);

#endif