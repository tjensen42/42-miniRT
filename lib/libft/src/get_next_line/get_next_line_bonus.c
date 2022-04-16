/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:30:27 by hepple            #+#    #+#             */
/*   Updated: 2022/04/15 11:26:46 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
 * Function that reads a line from file descriptor fd (returns NULL at EoF).
 */
char	*ft_get_next_line(int fd)
{
	static t_gnl_list	*lst = NULL;
	char				*buffer;
	int					bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (gnl_find_nl(lst_foc(&lst, fd)->stat) == -1 && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (gnl_free(buffer, &lst, fd));
		buffer[bytes_read] = '\0';
		lst_foc(&lst, fd)->stat = gnl_strjoin(lst_foc(&lst, fd)->stat, buffer);
	}
	if (lst_foc(&lst, fd)->stat == NULL || lst_foc(&lst, fd)->stat[0] == '\0')
		return (gnl_free(buffer, &lst, fd));
	free(buffer);
	return (get_line(&lst, fd));
}

/*
 * Function that splits stat into line (first part including one \n char) and
 * the new stat.
 */
char	*get_line(t_gnl_list **lst, int fd)
{
	t_gnl_list	*item;
	char		*tmp;
	char		*line;
	int			len;

	item = lst_foc(lst, fd);
	if (gnl_find_nl(item->stat) > -1)
	{
		tmp = item->stat;
		len = gnl_find_nl(item->stat) + 1;
		line = gnl_substr(item->stat, 0, len);
		item->stat = gnl_substr(item->stat, len, gnl_strlen(item->stat) - len);
		free(tmp);
	}
	else
	{
		line = gnl_substr(item->stat, 0, gnl_strlen(item->stat));
		lst_free(lst, fd);
	}
	return (line);
}

/*
 * Function that creates (with malloc) a new list item fd and initializes
 * its elements.
 */
t_gnl_list	*lst_new(int fd)
{
	t_gnl_list	*new_item;

	new_item = malloc(sizeof(t_gnl_list));
	if (new_item == NULL)
		return (NULL);
	new_item->fd = fd;
	new_item->stat = gnl_substr("", 0, 0);
	new_item->next = NULL;
	return (new_item);
}

/*
 * Function that either finds the existing list item fd or adds a new item fd
 * to the list.
 */
t_gnl_list	*lst_foc(t_gnl_list **lst, int fd)
{
	t_gnl_list	*tmp;

	if (*lst == NULL)
	{
		*lst = lst_new(fd);
		return (*lst);
	}
	if ((*lst)->fd == fd)
		return (*lst);
	tmp = *lst;
	while (tmp->next != NULL && tmp->next->fd != fd)
		tmp = tmp->next;
	if (tmp->next == NULL)
		tmp->next = lst_new(fd);
	return (tmp->next);
}

/*
 * Function that removes the item fd from the list and frees it and its stat
 * variable.
 */
void	lst_free(t_gnl_list **lst, int fd)
{
	t_gnl_list	*tmp;
	t_gnl_list	*free_item;

	if ((*lst)->next == NULL && (*lst)->fd == fd)
	{
		free_item = *lst;
		*lst = NULL;
	}
	else if ((*lst)->next != NULL && (*lst)->fd == fd)
	{
		free_item = *lst;
		*lst = (*lst)->next;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL && tmp->next->fd != fd)
			tmp = tmp->next;
		free_item = tmp->next;
		tmp->next = tmp->next->next;
	}
	free(free_item->stat);
	free(free_item);
}
