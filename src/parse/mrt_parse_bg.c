#include "mrt_parse.h"

int	parse_bg(t_scene *scene, char **split, int line_num)
{
	if (scene->bg.set == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (ft_split_count_str(split) != 3)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (parse_color(split[1], &(scene->bg.color[0])))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	if (parse_color(split[2], &(scene->bg.color[1])))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	scene->bg.set = true;
	return (0);
}
