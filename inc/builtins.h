/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:46:39 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/23 13:40:58 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		command_echo(t_msh *msh, t_exec *exec, int fd);
int		command_cd(t_msh *msh, t_exec *exec, int fd);
int		command_pwd(t_msh *msh, t_exec *exec, int fd);
int		command_env(t_msh *msh, t_exec *exec, int fd);
int		command_export(t_msh *msh, t_exec *exec, int fd);
int		command_unset(t_msh *msh, t_exec *exec, int fd);
int		command_exit(t_msh *msh, t_exec *exec, int fd);
void	sort_export_array(t_msh *msh);

#endif