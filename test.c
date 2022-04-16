// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <errno.h>
// #include <string.h>

// #define BUFFER_SIZE 10

// char	*ft_strchr(const char *s, int c);
// char	*ft_strjoin_free_s1(char const *s1, char const *s2);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// size_t	ft_strlen(const char *s);

// void	*ft_free_all(char *buf, char **read_str)
// {
// 	free(buf);
// 	free(*read_str);
// 	*read_str = NULL;
// 	return (NULL);
// }

// char	*ft_strjoin_free_s1(char const *s1, char const *s2)
// {
// 	size_t	joined_size;
// 	char	*joined_str;
// 	char	*tmp_s1;
// 	char	*tmp_joined_str;

// 	if (s1 == NULL)
// 		s1 = ft_substr("", 0, 0);
// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	joined_size = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	joined_str = malloc(joined_size * sizeof(char));
// 	if (joined_str == NULL)
// 		return (NULL);
// 	tmp_s1 = (char *)s1;
// 	tmp_joined_str = joined_str;
// 	while (*tmp_s1 != '\0')
// 		*tmp_joined_str++ = *tmp_s1++;
// 	while (*s2 != '\0')
// 		*tmp_joined_str++ = *s2++;
// 	*tmp_joined_str = '\0';
// 	free((char *)s1);
// 	return (joined_str);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s[len] != '\0')
// 		len++;
// 	return (len);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	char	*sub_str;

// 	if (s == NULL)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 		len = 0;
// 	sub_str = malloc((len + 1) * sizeof(char));
// 	if (sub_str == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < len && s[start + i] != '\0')
// 	{
// 		sub_str[i] = s[start + i];
// 		i++;
// 	}
// 	sub_str[i] = '\0';
// 	return (sub_str);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	int		i;
// 	char	*str;

// 	if (s == NULL)
// 		return (NULL);
// 	str = (char *)s;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == (char)c)
// 			return (&str[i]);
// 		i++;
// 	}
// 	if (str[i] == '\0' && c == '\0')
// 		return (&str[i]);
// 	return (NULL);
// }

// char	*process_next_line(char **rd_str)
// {
// 	int		chr_count;
// 	char	*tmp;
// 	char	*nxt_ln;

// 	if (ft_strchr(*rd_str, '\n'))
// 	{
// 		chr_count = ft_strchr(*rd_str, '\n') + 1 - *rd_str;
// 		nxt_ln = ft_substr(*rd_str, 0, chr_count);
// 		tmp = *rd_str;
// 		*rd_str = ft_substr(*rd_str, chr_count, ft_strlen(*rd_str) - chr_count);
// 		free(tmp);
// 	}
// 	else
// 	{
// 		nxt_ln = *rd_str;
// 		*rd_str = NULL;
// 	}
// 	return (nxt_ln);
// }

// char	*get_next_line(int fd)
// {
// 	int			chr_count;
// 	char		*buf;
// 	char		*nxt_ln;
// 	static char	*rd_str;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (buf == NULL)
// 		return (NULL);
// 	chr_count = 1;
// 	while (!ft_strchr(rd_str, '\n') && chr_count > 0)
// 	{
// 		chr_count = read(fd, buf, BUFFER_SIZE);
// 		if (chr_count == -1)
// 			return (ft_free_all(buf, &rd_str));
// 		buf[chr_count] = '\0';
// 		rd_str = ft_strjoin_free_s1(rd_str, buf);
// 	}
// 	if (rd_str[0] == '\0' || rd_str == NULL)
// 		return (ft_free_all(buf, &rd_str));
// 	nxt_ln = process_next_line(&rd_str);
// 	free(buf);
// 	return (nxt_ln);
// }


// int getline_gnu(char **lineptr, size_t *n, FILE *stream)
// {
// static char line[256];
// char *ptr;
// unsigned int len;

//    if (lineptr == NULL || n == NULL)
//    {
//       errno = EINVAL;
//       return -1;
//    }

//    if (ferror (stream))
//       return -1;

//    if (feof(stream))
//       return -1;

//    fgets(line,256,stream);

//    ptr = strchr(line,'\n');
//    if (ptr)
//       *ptr = '\0';

//    len = strlen(line);

//    if ((len+1) < 256)
//    {
//       ptr = realloc(*lineptr, 256);
//       if (ptr == NULL)
//          return(-1);
//       *lineptr = ptr;
//       *n = 256;
//    }

//    strcpy(*lineptr,line);
//    return(len);
// }

// int main(int argc, char* argv[])
// {
//     char* buffer = NULL;
//     size_t bufsize = 10;
//     ssize_t nbytes;
//     int counter = 0;
//     char error = 0;

//     FILE* input_fd = fopen(argv[1], "r");

//     // while ((nbytes = getline(&buffer, &bufsize, input_fd)) != -1)
//     // {
// 	// 	printf("%s %lu\n", buffer, bufsize);
//     //     counter += 1;
// 	// 	if (counter == 3)
// 	// 		break ;
//     // }

// 	buffer = get_next_line(fileno(input_fd));
// 	while (buffer)
//     {
// 		printf("%s", buffer);
//         counter += 1;
// 		if (counter == 3)
// 			break ;
//     	free(buffer);
// 		buffer = get_next_line(fileno(input_fd));
//     }
// 	free(buffer);
//     fclose(input_fd);

//     return 0;
// }

#define BUFSIZE 1000000000
int	main(void)
{
	static char buf[BUFSIZE];

	for (int i = 0; i < BUFSIZE; i++)
		buf[i] = 42;
}


