/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 08:40:20 by hepple            #+#    #+#             */
/*   Updated: 2021/10/22 11:30:32 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Helper function that frees an array of strings generated with ft_split.
 */
static void	free_split(char ***split)
{
	int	i;

	i = 0;
	while ((*split)[i] != NULL)
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}

/*
 * Helper function that frees an array of strings generated with ft_split.
 */
static unsigned int	count_words(char const *str, char c)
{
	unsigned int	word;
	unsigned int	i;

	if (str[0] == '\0')
		return (0);
	i = 1;
	word = 0;
	if (str[0] != c)
		word++;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i - 1] == c)
			word++;
		i++;
	}
	return (word);
}

/*
 * Helper function that frees an array of strings generated with ft_split.
 */
static void	copy_one_word(char *dst, char const *src, char c)
{
	unsigned int	i;

	i = 0;
	while (src[i] != c && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

/*
 * Helper function that frees an array of strings generated with ft_split.
 */
static int	copy_words(char const *str, char c, char **dst)
{
	unsigned int	word;
	unsigned int	letter;
	unsigned int	i;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			letter = 0;
			while (str[i + letter] != c && str[i + letter] != '\0')
				letter++;
			dst[word] = malloc(sizeof(char) * (letter + 1));
			if (dst[word] == NULL)
				return (-1);
			copy_one_word(dst[word], str + i, c);
			word++;
			i = i + letter;
		}
		else
			i++;
	}
	return (0);
}

/*
 * Function that returns an array of strings obtained by splitting the
 * string 's' at every character 'c'. The array contains a NULL pointer
 * as a last element.
 */
char	**ft_split(char const *s, char c)
{
	char			**result;
	unsigned int	word_count;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (result == NULL)
		return (NULL);
	result[word_count] = NULL;
	if (copy_words(s, c, result) == -1)
		free_split(&result);
	return (result);
}
