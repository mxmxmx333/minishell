/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:01:35 by mbonengl          #+#    #+#             */
/*   Updated: 2024/09/26 14:21:18 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"

char *get_host_name()
{
    char    *hostname;
    int     fd;
    int     i;

    fd = open("/etc/hostname", O_RDONLY);
    if (fd == -1)
       return (perror("Failed to open hostname file."), NULL);
    i = 0;
    hostname = get_next_line(fd);
    if (!hostname)
        return (NULL);
    i = ft_strlen(hostname) - 1;
    hostname[i] = '\0';
    return (hostname);
}

int check_home_dir(char *str)
{
    char    *home;
    int     len;
    
    home = getenv("HOME");
    len = ft_strlen(home);
    if (ft_strncmp(home, str, len) == 0)
        return (1);
    return (0);
}

char    *concatenate_prompt(char *s1, char *s2, char *s3)
{
    char    *prompt;
    char    *home;
    int     i;
    int     homelen;

    i = 0;
    home = getenv("HOME");
    homelen = ft_strlen(home);
    if (check_home_dir(s3))
        s3 = s3 + homelen;
    prompt = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 6, sizeof(char));
    if (!prompt)
        perror("malloc fail");
    while (*s1)
        prompt[i++] = *s1++;
    prompt[i++] = '@';
    while (*s2)
        prompt[i++] = *s2++;
    prompt[i++] = ':';
    prompt[i++] = '~';
    while (*s3)
        prompt[i++] = *s3++;
    prompt[i++] = '$';
    prompt[i++] = ' ';
    prompt[i++] = '\0';
    return (prompt);
}

int create_prompt(t_msh *msh)
{
    char    *line;
    char    *username;
    char    *hostname;

    username = getenv("USER");
    msh->cur_dir = getenv("PWD");
    hostname = get_host_name();
    line = concatenate_prompt(username, hostname, msh->cur_dir);
    msh->prompt = line;

    return (0);
}