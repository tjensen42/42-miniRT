#include "miniRT.h"
#include "scene.h"

static int	parse_options(t_scene *scene, char **argv);
static int	parse_file(t_scene *scene, int file_fd);
static int	parse_line(t_scene *scene, char *line, int line_num);
static int	parse_identifier(t_scene *scene, char **split, int line_num);

int	scene_parser(t_scene *scene, int argc, char **argv)
{
	int		file_fd;

	if (argc != 2 && argc != 3)
		return (scene_print_error(-1, ERR_USAGE, NULL, NULL));
	file_fd = scene_open_rt_file(argv[1]);
	if (file_fd == -1)
		return (ERROR);
	if (parse_options(scene, argv) || parse_file(scene, file_fd))
	{
		close(file_fd);
		return (ERROR);
	}
	close(file_fd);
	return (0);
}

static int	parse_options(t_scene *scene, char **argv)
{
	if (argv[2])
	{
		if (ft_strcmp(argv[2], "--ppm") == 0)
			scene->img.ppm = true;
		else
		{
			scene_print_error(-1, ERR_INVAL_OPTION, ERR_USAGE, NULL);
			return (ERROR);
		}
	}
	return (0);
}

static int	parse_file(t_scene *scene, int file_fd)
{
	int		line_num;
	char	*line;

	line_num = 1;
	line = ft_gnl_without_buffer(file_fd);
	while (line)
	{
		if (parse_line(scene, line, line_num) == ERROR)
		{
			free(line);
			return (ERROR);
		}
		free(line);
		line = ft_gnl_without_buffer(file_fd);
		line_num++;
	}
	return (0);
}

static int	parse_line(t_scene *scene, char *line, int line_num)
{
	int		error;
	char	**split;

	error = false;
	if (ft_strchr(line, '\t'))
		return (scene_print_error(line_num, ERR_FILE_TABS, NULL, NULL));
	if (line[0] != '\0')
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		split = ft_split(line, ' ');
		if (split == NULL)
			return (scene_print_error(-1, ERR_PARSE, strerror(ENOMEM), NULL));
		if (split[0] && split[0][0] != '#')
			error = parse_identifier(scene, split, line_num);
		ft_free_split(&split);
	}
	return (error);
}

static const struct s_ident	g_ident[] = {
{IDENT_RES, &process_img},
{IDENT_SAMPLING, &process_sampling},
{IDENT_CAM, &process_cam},
{IDENT_BG, &process_bg},
{IDENT_AMB, &process_amb},
{IDENT_LIGHT, NULL},
{IDENT_PLANE, &process_plane},
{IDENT_SPHERE, &process_sphere},
{IDENT_CYLINDER, NULL},
{NULL, NULL}
};

static int	parse_identifier(t_scene *scene, char **split, int line_num)
{
	int	i;

	i = 0;
	while (g_ident[i].ident)
	{
		if (ft_strcmp(split[0], g_ident[i].ident) == 0)
			return (g_ident[i].process_ident(scene, split, line_num));
		i++;
	}
	scene_print_error(line_num, ERR_INVAL_IDENT, split[0], NULL);
	return (ERROR);
}
