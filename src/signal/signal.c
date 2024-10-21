/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:57:11 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/10/17 15:27:55 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

/*
	Signal handler for SIGINT.
*/
void	handle_sigint(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
}

/*
	Signal handler for SIGQUIT.
*/
void	handle_sigquit(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
