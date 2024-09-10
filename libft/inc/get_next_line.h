/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:36:26 by mbonengl          #+#    #+#             */
/*   Updated: 2024/08/14 13:59:06 by mbonengl         ###   ########.fr       */
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