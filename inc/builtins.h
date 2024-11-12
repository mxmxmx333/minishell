/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:46:39 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/07 18:36:25 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int			command_echo(t_msh *msh, t_exec *exec, int fd);
int			command_cd(t_msh *msh, t_exec *exec, int fd);
int			command_pwd(t_msh *msh, t_exec *exec, int fd);
int			command_env(t_msh *msh, t_exec *exec, int fd);
int			command_export(t_msh *msh, t_exec *exec, int fd);
int			command_unset(t_msh *msh, t_exec *exec, int fd);
int			command_exit(t_msh *msh, t_exec *exec, int fd);
int			check_valid(t_msh *msh, char *v_name);
void		sort_export_array(t_msh *msh);
long long	ft_atoi_custom(const char *nptr);
int			check_newline(t_exec *exec);
void		dis_export_err(char *cmdname, char *arg, char *errmsg);
char		*env_variable_finder(t_msh *msh, char *node);
void		export_error(char *v_name, char *v_value, int *status);
int			find_v_value(char *arg);

#endif