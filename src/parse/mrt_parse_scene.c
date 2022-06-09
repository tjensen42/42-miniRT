/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:24 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:56:24 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (print_error_scene(-1, ERR_PARSE, ERR_FILE, file));
	fp = fopen(file, "r");
	if (fp == NULL)
		return (print_error_scene(-1, ERR_PARSE, strerror(errno), file));
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
		return (print_error_scene(line_num, ERR_PARSE, ERR_FILE_TABS, NULL));
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
{ID_RES, &parse_res},
{ID_SAMPLING, &parse_sampling},
{ID_CAM, &parse_cam},
{ID_BG, &parse_bg},
{ID_AMB, &parse_amb},
{ID_LIGHT_SP, &parse_light_sphere},
{ID_LIGHT_DI, &parse_light_disc},
{ID_LIGHT_RT, &parse_light_rectangle},
{ID_PLANE, &parse_obj_plane},
{ID_SPHERE, &parse_obj_sphere},
{ID_CYLINDER, &parse_obj_cylinder},
{ID_RECTANGLE, &parse_obj_rectangle},
{ID_CUBOID, &parse_obj_cuboid},
{ID_DISC, &parse_obj_disc},
{ID_TUBE, &parse_obj_tube},
{ID_TEXTURE, &parse_texture},
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
	print_error_scene(line_num, ERR_PARSE, ERR_ID, split[0]);
	return (-1);
}
