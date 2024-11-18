/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:57:24 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/13 14:48:53 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include "minishell.h"

void	handle_sigint(int signum);
void	handle_sigquit(int signum);
void	handle_sigint_child(int signum);
void	handle_sigint_heredoc(int signum);

#endif