#include "mrt_parse.h"

static int	str_to_surfaces(const char *str, double surf[4], int line_num);

int	parse_material(t_material *material, char **split, int line_num)
{
	double	surf_sum;

	if (parse_color(split[0], &(material->color)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	if (str_to_surfaces(split[1], material->surface, line_num))
		return (-1);
	surf_sum = material->surface[SURF_DIFFUSE]
		+ material->surface[SURF_SPECULAR]
		+ material->surface[SURF_DIELECTRIC]
		+ material->surface[SURF_EMISSION];
	if (surf_sum != 1.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_SURF, NULL));
	if (double_from_str(split[2], 1, 2, &(material->fuzz))
		|| material->fuzz < 0.0 || material->fuzz > 9.99)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_FUZZ, NULL));
	if (double_from_str(split[3], 1, 2, &(material->refraction_index))
		|| (material->surface[SURF_DIELECTRIC] > 0.0
		&& (material->refraction_index < 1.0 || material->refraction_index > 2.0)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_REFRAC, NULL));
	material->brightness = 1.0;
	material->get_color = &obj_color;
	return (0);
}

static int	str_to_surfaces(const char *str, double surf[4], int line_num)
{
	int		error;
	char	**split_surf;

	error = false;
	split_surf = ft_split(str, ',');
	if (split_surf == NULL)
		return (print_error_scene(-1, ERR_PARSE, strerror(errno), NULL));
	if (ft_split_count_str(split_surf) != 4)
		error = -1;
	if (!error)
		error = double_from_str(split_surf[0], 1, 2, &(surf[SURF_DIFFUSE]));
	if (!error)
		error = double_from_str(split_surf[1], 1, 2, &(surf[SURF_SPECULAR]));
	if (!error)
		error = double_from_str(split_surf[2], 1, 2, &(surf[SURF_DIELECTRIC]));
	if (!error)
		error = double_from_str(split_surf[3], 1, 2, &(surf[SURF_EMISSION]));
	if (error)
		error = print_error_scene(line_num, ERR_PARSE, ERR_INVAL_SURF, NULL);
	ft_free_split(&split_surf);
	return (error);
}
