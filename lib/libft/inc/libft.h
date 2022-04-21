/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:54:31 by hepple            #+#    #+#             */
/*   Updated: 2022/04/20 11:55:30 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ******************* */
/*   I N C L U D E S   */
/* ******************* */

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# include "get_next_line_bonus.h"
# include "ft_printf.h"

/* ******************* */
/*    D E F I N E S    */
/* ******************* */

# define BASE_BIN "01"
# define BASE_DEC "0123456789"
# define BASE_HEX_LOWER "0123456789abcdef"
# define BASE_HEX_UPPER "0123456789ABCDEF"

/* ******************* */
/*   T Y P E D E F S   */
/* ******************* */

/*
 * Linked list:
 * - content:	void pointer to content
 * - next:		pointer to the next element
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ******************* */
/* P R O T O T Y P E S */
/* ******************* */

/* Part 1 */

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

/* Part 2 */

char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* Bonus Part */

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

/* Additional Functions */

void	ft_free_split(char ***split);
int		ft_split_count_str(char **split);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_gnl_without_buffer(int fd);
int		ft_strncmp_rev(const char *s1, const char *s2, size_t n);
int		ft_str_count_chr(const char *str, const char c);
double	ft_rand_double(double min, double max);
double	ft_rand_double_0_1(void);
int		print_error(char *s1, char *s2, char *s3, char *s4);

#endif
