/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:46:39 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/14 15:04:12 by nicvrlja         ###   ########.fr       */
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
int			check_valid(char *arg);
void		sort_export_array(t_msh *msh);
long long	ft_atoi_custom(const char *nptr);
int			check_newline(t_exec *exec);
void		dis_export_err(char *cmdname, char *arg, char *errmsg);
char		*env_variable_finder(t_msh *msh, char *node);
void		export_error(char *v_name, char *v_value, int *status);
int			find_v_value(char *arg);
void		cd_errors(t_msh *msh, int errcode, char *arg);
t_env	*env_node_finder(t_msh *msh, char *node);
int		args_numb(char **args);
int	change_directory(t_msh *msh, char *dir);
void	add_node_env(t_msh *msh, char *v_name, char *v_value);
void	print_export_array(t_msh *msh, int fd);
void	create_oldpwd_node(t_msh *msh, char *oldpwd);
void	create_pwd_node(t_msh *msh, char *pwd);
void	remove_env_node(t_msh *msh, t_env *node);

#endif