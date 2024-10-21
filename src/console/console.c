/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:01:35 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/21 16:39:51 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"

/*
	Checks if the path starts with /home/username
*/
static int	check_home_dir(t_msh *msh, char *str)
{
	int	len;

	len = ft_strlen(msh->home_dir);
	if (ft_strncmp(msh->home_dir, str, len) == 0)
		return (1);
	return (0);
}

/*
	Concatenate username@hostname:~/current_work_dir$ 
	~ represents home directory
*/
static char	*concatenate_prompt(t_msh *msh, char *s1, char *s2, char *s3)
{
	char	*prompt;
	int		i;
	int		homelen;

	i = 0;
	homelen = ft_strlen(msh->home_dir);
	if (check_home_dir(msh, s3))
		s3 = s3 + homelen;
	prompt = ft_calloc(ft_strlen(s1) + ft_strlen(s2)
			+ ft_strlen(s3) + 5 + 4, sizeof(char));
	if (!prompt)
		return (perror("malloc fail"), NULL);
	while (*s1)
		prompt[i++] = *s1++;
	prompt[i++] = '@';
	while (*s2)
		prompt[i++] = *s2++;
	prompt[i++] = ':';
	prompt[i++] = '~';
	while (*s3)
		prompt[i++] = *s3++;
	ft_strlcpy(prompt + i, "🦫", 4 + 1);
	i += 4;
	prompt[i++] = ' ';
	return (prompt);
}

/*
	Function which will create the prompt message.
	It will update msh->cur_dir each time its run.
*/
int	create_prompt(t_msh *msh)
{
	char	*line;

	msh->cur_dir = getcwd(NULL, 0);
	if (!msh->cur_dir || !msh->username || !msh->hostname)
		return (1);
	line = concatenate_prompt(msh, msh->username, msh->hostname, msh->cur_dir);
	msh->prompt = line;
	return (0);
}
