#include "miniRT.h"
#include "scene.h"

static int	parse_file(t_scene *scene, FILE *fp);
static int	parse_line(t_scene *scene, char *line, int line_num);
static int	parse_identifier(t_scene *scene, char **split, int line_num);

int	scene_parser(t_scene *scene, int argc, char **argv)
{
	int		error;
	FILE	*fp;

	if (argc != 2)
		return (scene_print_error(-1, ERR_USAGE, NULL, NULL));
	fp = scene_open_rt_file(argv[1]);
	if (fp == NULL)
		return (ERROR);
	error = parse_file(scene, fp);
	fclose(fp);
	return (error);
}

static int	parse_file(t_scene *scene, FILE *fp)
{
	int		error;
	char	*line;
	size_t	line_size;
	int		line_num;

	error = false;
	line = NULL;
	line_size = 0;
	line_num = 1;
	while (!error && getline(&line, &line_size, fp) > 0)
	{
		error = parse_line(scene, line, line_num);
		line_num++;
	}
	free(line);
	return (error);
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
{IDENT_PPM, &process_ppm},
{IDENT_RES, &process_img},
{IDENT_SAMPLING, &process_sampling},
{IDENT_CAM, &process_cam},
{IDENT_BG, &process_bg},
{IDENT_AMB, &process_amb},
{IDENT_LIGHT, NULL},
{IDENT_PLANE, &process_plane},
{IDENT_SPHERE, &process_sphere},
{IDENT_CYLINDER, &process_cylinder},
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
