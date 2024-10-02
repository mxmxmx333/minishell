/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:59:40 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/02 16:22:58 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <unistd.h> /*read*/
# include <stdlib.h> /*malloc/free/size_t*/

typedef struct bufferlist
{
	char				*str;
	struct bufferlist	*next;
}	t_list;

void	resetlist(t_list **b_list);
char	*takeline(t_list *b_list);
int		copycontent(int fd, t_list **b_list);
char	*get_next_line(int fd);
void	lstclear(t_list **blist);
void	setupnext(t_list **b_list, char *n_buff);
size_t	getlinelen(t_list *b_list);
void	ft_lstadd_back_gnl(t_list **lst, char *buffer);
int		no_nl(t_list *list);

#endif