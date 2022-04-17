#include "scene.h"

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

static int	check_file_ending(const char *file, const char *ending);

FILE	*scene_open_rt_file(const char *file)
{
	FILE	*fp;

	if (file == NULL)
		return (NULL);
	if (check_file_ending(file, SCENE_FILE_ENDING) == ERROR)
	{
		scene_print_error(-1, file, ERR_INVAL_FILE, NULL);
		return (NULL);
	}
	fp = fopen(file, "r");
	if (fp == NULL)
		scene_print_error(-1, file, strerror(errno), NULL);
	return (fp);
}

static int	check_file_ending(const char *file, const char *ending)
{
	size_t	i;

	if (file == NULL || ending == NULL)
		return (ERROR);
	if (ft_strlen(file) <= ft_strlen(ending))
		return (ERROR);
	i = 0;
	while (i < ft_strlen(ending))
	{
		if (file[ft_strlen(file) - 1 - i] != ending[ft_strlen(ending) - 1 - i])
			return (ERROR);
		i++;
	}
	return (0);
}
