#include "mrt_parse.h"
#include "print/mrt_print.h"

static int	parse_file(t_scene *scene, FILE *fp);
static int	parse_line(t_scene *scene, char *line, int line_num);
static int	parse_identifier(t_scene *scene, char **split, int line_num);

int	parse_scene(t_scene *scene, const char *file)
{
	int		error;
	FILE	*fp;

	if (file && ft_strncmp_rev(file, ".rt", 3) != 0)
	{
		print_error_scene(-1, file, ERR_INVAL_FILE, NULL);
		return (-1);
	}
	fp = fopen(file, "r");
	if (fp == NULL)
		return (print_error_scene(-1, file, strerror(errno), NULL));
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
		return (print_error_scene(line_num, ERR_FILE_TABS, NULL, NULL));
	if (line[0] != '\0' && line[0] != '\n' && line[0] != '#')
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		split = ft_split(line, ' ');
		if (split == NULL)
			return (print_error_scene(-1, ERR_PARSE, strerror(ENOMEM), NULL));
		if (split[0] && split[0][0] != '#')
			error = parse_identifier(scene, split, line_num);
		ft_free_split(&split);
	}
	return (error);
}

static const struct s_ident	g_ident[] = {
{IDENT_RES, &parse_img},
{IDENT_SAMPLING, &parse_sampling},
{IDENT_CAM, &parse_cam},
{IDENT_BG, &parse_bg},
{IDENT_AMB, &parse_amb},
{IDENT_LIGHT, &parse_is},
{IDENT_PLANE, &parse_obj_plane},
{IDENT_SPHERE, &parse_obj_sphere},
{IDENT_CYLINDER, &parse_obj_cylinder},
{IDENT_RECTANGLE, &parse_obj_rectangle},
{IDENT_CUBOID, &parse_obj_cuboid},
{IDENT_DISC, &parse_obj_disc},
{IDENT_TUBE, &parse_obj_tube},
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
	print_error_scene(line_num, ERR_INVAL_IDENT, split[0], NULL);
	return (-1);
}
