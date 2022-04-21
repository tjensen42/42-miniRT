#include "mrt_parse.h"

int parse_img(t_scene *scene, char **split, int line_num)
{
	if (scene->img.res_set == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (ft_split_count_str(split) != 3)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (int_from_str(split[1], 100, 10000, &(scene->img.width)) == -1)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid resolution (range [100-10000])", NULL));
	if (int_from_str(split[1], 100, 10000, &(scene->img.height)) == -1)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid resolution (range [100-10000])", NULL));
	scene->img.res_set = true;
	return (0);
}
