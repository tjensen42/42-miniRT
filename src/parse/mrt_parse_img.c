#include "mrt_parse.h"

int	parse_img(t_scene *scene, char **split, int line_num)
{
	if (scene->img.res_set == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (ft_split_count_str(split) != 3)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (int_from_str(split[1], 10, 10000, &(scene->img.width)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_RES, NULL));
	if (int_from_str(split[2], 10, 10000, &(scene->img.height)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_RES, NULL));
	scene->img.res_set = true;
	return (0);
}
