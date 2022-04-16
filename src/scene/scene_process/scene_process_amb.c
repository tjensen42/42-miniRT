#include "miniRT.h"
#include "../scene.h"

int	process_amb(t_scene *scene, char **split, int line_num)
{
	if (scene->amb.set == true)
		return (scene_print_error(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (split_count(split) != 3)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (str_to_double(split[1], 4, 2, &(scene->amb.brightness)))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_BRIGHT, NULL));
	if (str_to_color(split[2], &(scene->amb.color)))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	scene->amb.set = true;
	return (0);
}
