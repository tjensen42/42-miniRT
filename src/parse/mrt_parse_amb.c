#include "mrt_parse.h"

int	parse_amb(t_scene *scene, char **split, int line_num)
{
	if (scene->amb.set == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (ft_split_count_str(split) != 3)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (double_from_str(split[1], 1, 2, &(scene->amb.brightness))
		|| scene->amb.brightness < 0.0 || scene->amb.brightness > 1.0)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid ratio", NULL));
	if (parse_color(split[2], &(scene->amb.color)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	scene->amb.color = color_scale(scene->amb.brightness, scene->amb.color);
	scene->amb.set = true;
	return (0);
}
