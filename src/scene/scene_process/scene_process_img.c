#include "miniRT.h"
#include "../scene.h"

int process_img(t_scene *scene, char **split, int line_num)
{
	if (scene->img.res_set == true)
		return (scene_print_error(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (split_count(split) != 3)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (str_to_int(split[1], 100, 10000, &(scene->img.width)) == ERROR)
		return (scene_print_error(line_num, ERR_PARSE, "Invalid resolution (range [100-10000])", NULL));
	if (str_to_int(split[1], 100, 10000, &(scene->img.height)) == ERROR)
		return (scene_print_error(line_num, ERR_PARSE, "Invalid resolution (range [100-10000])", NULL));
	scene->img.res_set = true;
	return (0);
}
