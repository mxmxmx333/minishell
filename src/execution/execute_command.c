/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:54:05 by mbonengl          #+#    #+#             */
/*   Updated: 2024/11/15 11:28:13 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_find_(t_msh *msh, t_env *env, char *name)
{
	t_env	*new;

	while (env->next)
	{
		if (!ft_strnrealcmp(env->v_name, name, ft_strlen(name)))
			return (env);
		env = env->next;
	}
	if (!ft_strnrealcmp(env->v_name, name, ft_strlen(name)))
		return (env);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (error_simple(msh, M_ERR, 1), NULL);
	new->v_name = ft_strdup("_");
	new->v_value = ft_strdup("");
	env->next = new;
	return (new);
}

void	handle_redirections(t_msh *msh, t_exec *current)
{
	t_tok	*redirections;

	redirections = current->redirections;
	redirect_inpipe(msh, current);
	redirect_outpipe(msh, current);
	close_both_pipes(msh, current);
	while (redirections)
	{
		if (redirections->type == REDI_IN || redirections->type == HERE_DOC)
		{
			redirect_input(msh, redirections);
		}
		else
			redirect_output(msh, redirections);
		redirections = redirections->next;
	}
}

void	implement_command(t_msh *msh, t_exec *current)
{
	t_env	*env;
	char	*tmp;

	if (!current->args || !current->args[0])
		return ;
	pathfinder(msh, current->args[0]);
	env = env_find_(msh, msh->env, "_");
	tmp = env->v_value;
	env->v_value = ft_strdup(current->args[0]);
	free(tmp);
	if (!env->v_value)
		return (error_simple(msh, M_ERR, 1));
	destroy_exp(msh);
	convert_exp(msh);
	execve(msh->exe_path, current->args, msh->export);
	destroy_exe_path(msh);
}

int	execute_command(t_msh *msh, t_exec *current)
{
	pid_t	pid;

	pid = wrppd_fork(msh);
	if (is_parent(pid))
	{
		signal(SIGINT, SIG_IGN);
		msh->last_pid = pid;
		close_previous_pipe(msh, current);
	}
	else
	{
		signal(SIGINT, handle_sigint_child);
		signal(SIGQUIT, handle_sigquit);
		handle_redirections(msh, current);
		if (current->args && (!ft_strnrealcmp(current->args[0], ".", 1) || !ft_strnrealcmp(current->args[0], "..", 2)))
			error_complex(msh, CMDNF_ERR, current->args[0], 127);
		if (!current->lonely && current->args && current->args[0])
			implement_command(msh, current);
		exit_success(msh);
	}
	return (0);
}
