/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:28:12 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/11/04 16:15:24 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

void	handle_sigint_child(int signum)
{
	int	*status;

	(void)signum;
	status = get_status(NULL);
	*status = 130;
	//rl_on_new_line();
	//rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
}

/*
	Signal handler for SIGINT.
*/
void	handle_sigint(int signum)
{
	int	*status;

	(void)signum;
	status = get_status(NULL);
	*status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();

}

void	handle_sigquit(int signum)
{
	(void)signum;
	printf("Quit (core dumped)\n");
}
