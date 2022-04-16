#include "miniRT.h"
#include "../scene.h"

int	process_bg(t_scene *scene, char **split, int line_num)
{
	if (scene->bg_set == true)
		return (scene_print_error(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (split_count(split) != 3)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (str_to_color(split[1], &(scene->bg[0])))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	if (str_to_color(split[2], &(scene->bg[1])))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	scene->bg_set = true;
	return (0);
}
