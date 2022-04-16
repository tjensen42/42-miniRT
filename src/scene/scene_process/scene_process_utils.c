#include "miniRT.h"
#include "../scene.h"

static double	get_double(const char *str);
static int	str_to_surfaces(const char *str, double surf[4]);

int	process_material(t_material *material, char **split, int line_num)
{
	if (str_to_color(split[0], &(material->color)))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	if (str_to_surfaces(split[1], material->surface))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_SURF, NULL));
	if (str_to_double(split[2], 1, 1, &(material->fuzz)))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_FUZZ, NULL));
	if (str_to_double(split[3], 1, 1, &(material->refraction_index)))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_REFRAC, NULL));
	return (0);
}

static int	str_to_surfaces(const char *str, double surf[4])
{
	int		error;
	char	**split_surf;

	error = false;
	split_surf = ft_split(str, ',');
	if (split_surf == NULL)
		return (scene_print_error(-1, ERR_PARSE, strerror(ENOMEM), NULL));
	if (split_count(split_surf) != 4)
		error = ERROR;
	if (!error)
		error = str_to_double(split_surf[0], 1, 1, &(surf[SURF_DIFFUSE]));
	if (!error)
		error = str_to_double(split_surf[1], 1, 1, &(surf[SURF_SPECULAR]));
	if (!error)
		error = str_to_double(split_surf[2], 1, 1, &(surf[SURF_DIELECTRIC]));
	if (!error)
		error = str_to_double(split_surf[3], 1, 1, &(surf[SURF_EMISSION]));
	ft_free_split(&split_surf);
	return (error);
}

int	str_to_vec3(const char *str, t_vec3 *vec3)
{
	char	**split;

	if (str_count_chr(str, ',') != 2)
		return (ERROR);
	split = ft_split(str, ',');
	if (split == NULL || split_count(split) != 3)
		return (ERROR);
	if (str_to_double(split[0], 6, 6, &((*vec3).x)))
		return (ERROR);
	if (str_to_double(split[1], 6, 6, &((*vec3).y)))
		return (ERROR);
	if (str_to_double(split[2], 6, 6, &((*vec3).z)))
		return (ERROR);
	ft_free_split(&split);
	return (0);
}

int	str_to_color(const char *str, t_color *color)
{
	char	**split;
	int		primary;
	int		i;

	if (str_count_chr(str, ',') != 2)
		return (ERROR);
	split = ft_split(str, ',');
	if (split == NULL)
		return (ERROR);
	i = 0;
	while (i < 3)
	{
		if (str_to_int(split[i], 0, 255, &primary) == ERROR)
			return (ERROR);
		if (i == 0)
			(*color).r = (double)primary / 255.0;
		else if (i == 1)
			(*color).g = (double)primary / 255.0;
		else if (i == 2)
			(*color).b = (double)primary / 255.0;
		i++;
	}
	ft_free_split(&split);
	return (0);
}

int	str_to_int(const char *str, int min, int max, int *res)
{
	int	i;

	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (ERROR);
		i++;
	}
	*res = ft_atoi(str);
	if (*res < min || *res > max)
		return (ERROR);
	return (0);
}

int	str_to_double(const char *str, int before_point, int after_point, double *res)
{
	int	i;

	if (ft_strchr(str, '.') != ft_strrchr(str, '.'))
		return (ERROR);
	if (ft_strchr(str, '.') && (int)(ft_strchr(str, '.') - str) > before_point)
		return (ERROR);
	if (ft_strchr(str, '.') && (int)(ft_strlen(ft_strchr(str, '.') + 1)) > after_point)
		return (ERROR);
	if (ft_strchr(str, '.') && !ft_isdigit(*(ft_strchr(str, '.') + 1)))
		return (ERROR);
	if (!ft_strchr(str, '.') && (int)(ft_strlen(str)) > before_point)
		return (ERROR);
	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (ERROR);
		i++;
	}
	*res = get_double(str);
	return (0);
}

static double	get_double(const char *str)
{
	double	value;
	double	factor;
	int		i;

	i = 0;
	value = 0.0;
	factor = 1;
	if (str[i] == '-')
		factor = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10.0 + (str[i] - '0');
		factor = factor / 10.0;
		i++;
	}
	return (factor * value);
}

int	split_count(char **split)
{
	int	i;

	if (split == NULL)
		return (-1);
	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	str_count_chr(const char *str, const char c)
{
	int		i;
	int		chr_count;

	if (str == NULL)
		return (-1);
	chr_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			chr_count++;
		i++;
	}
	return (chr_count);
}
