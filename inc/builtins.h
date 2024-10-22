/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:46:39 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/22 13:45:51 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	command_echo(t_msh *msh, t_exec *exec, int fd);
int	command_cd(t_msh *msh, t_exec *exec, int fd);
int	command_pwd(t_msh *msh, t_exec *exec, int fd);
int	command_env(t_msh *msh, t_exec *exec, int fd);
int	command_export(t_msh *msh, t_exec *exec, int fd);

#endif