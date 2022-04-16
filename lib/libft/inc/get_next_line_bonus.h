/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:30:30 by hepple            #+#    #+#             */
/*   Updated: 2021/11/18 09:54:18 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

/* ******************* */
/*   I N C L U D E S   */
/* ******************* */

# include <unistd.h>
# include <stdlib.h>

/* ******************* */
/*    D E F I N E S    */
/* ******************* */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* ******************* */
/*   T Y P E D E F S   */
/* ******************* */

/*
 * Linked list to save the stat variables for each file descriptor fd:
 * - fd:	file descriptor
 * - stat:	static variable for file descriptor fd
 * - next:	pointer to the next element in the list
 */
typedef struct s_gnl_list
{
	int					fd;
	char				*stat;
	struct s_gnl_list	*next;
}						t_gnl_list;

/* ******************* */
/* P R O T O T Y P E S */
/* ******************* */

/* get_next_line_bonus.c */

char		*ft_get_next_line(int fd);
char		*get_line(t_gnl_list **lst, int fd);
t_gnl_list	*lst_new(int fd);
t_gnl_list	*lst_foc(t_gnl_list **lst, int fd);
void		lst_free(t_gnl_list **lst, int fd);

/* get_next_line_utils_bonus.c */

int			gnl_find_nl(char *str);
int			gnl_strlen(char *str);
char		*gnl_strjoin(char *s1, char *s2);
char		*gnl_substr(char *s, int start, int len);
void		*gnl_free(char *buffer, t_gnl_list **lst, int fd);

#endif
