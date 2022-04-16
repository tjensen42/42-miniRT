#include "scene.h"

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

static int	check_file_ending(const char *file, const char *ending);

int	scene_open_rt_file(const char *input_file)
{
	int	file_fd;

	if (input_file == NULL)
		return (-1);
	if (check_file_ending(input_file, FILE_ENDING) == ERROR)
	{
		scene_print_error(-1, input_file, ERR_INVAL_FILE, NULL);
		return (-1);
	}
	file_fd = open(input_file, O_RDONLY, 0);
	if (file_fd == -1)
		scene_print_error(-1, input_file, strerror(errno), NULL);
	return (file_fd);
}

static int	check_file_ending(const char *file, const char *ending)
{
	size_t	i;

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
