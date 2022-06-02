#include "mrt_parse.h"

static int	str_to_surfaces(const char *str, double surf[4]);

int	parse_material(t_material *material, char **split, int line_num)
{
	int		i;
	double	surf_sum;

	if (parse_color(split[0], &(material->color)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	if (str_to_surfaces(split[1], material->surface))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_SURF, NULL));
	if (double_from_str(split[2], 1, 1, &(material->fuzz)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_FUZZ, NULL));
	if (double_from_str(split[3], 1, 1, &(material->refraction_index)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_REFRAC, NULL));
	i = 0;
	surf_sum = 0;
	while (i < 4)
	{
		surf_sum += material->surface[i];
		i++;
	}
	if (surf_sum != 1.0)
		return (print_error_scene(line_num, ERR_PARSE, "surf_sum not equal to 1.0", NULL));
	material->brightness = 1.0;
	material->get_color = &obj_color;
	return (0);
}

static int	str_to_surfaces(const char *str, double surf[4])
{
	int		error;
	char	**split_surf;

	error = false;
	split_surf = ft_split(str, ',');
	if (split_surf == NULL)
		return (print_error_scene(-1, ERR_PARSE, strerror(ENOMEM), NULL));
	if (ft_split_count_str(split_surf) != 4)
		error = -1;
	if (!error)
		error = double_from_str(split_surf[0], 1, 1, &(surf[SURF_DIFFUSE]));
	if (!error)
		error = double_from_str(split_surf[1], 1, 1, &(surf[SURF_SPECULAR]));
	if (!error)
		error = double_from_str(split_surf[2], 1, 1, &(surf[SURF_DIELECTRIC]));
	if (!error)
		error = double_from_str(split_surf[3], 1, 1, &(surf[SURF_EMISSION]));
	ft_free_split(&split_surf);
	return (error);
}
