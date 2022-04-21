#include "mrt_parse.h"

int parse_ppm(t_scene *scene, char **split, int line_num)
{
	if (scene->img.ppm == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (ft_split_count_str(split) != 2)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	scene->img.fp_ppm = fopen(split[1], "w");
	if (scene->img.fp_ppm == NULL)
		return (print_error_scene(line_num, ERR_PARSE, split[1], strerror(errno)));
	scene->img.ppm = true;
	return (0);
}
