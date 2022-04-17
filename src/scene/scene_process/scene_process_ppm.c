#include "miniRT.h"
#include "../scene.h"

int process_ppm(t_scene *scene, char **split, int line_num)
{
	if (scene->img.ppm == true)
		return (scene_print_error(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (split_count(split) != 2)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	scene->img.fp_ppm = fopen(split[1], "w");
	if (scene->img.fp_ppm == NULL)
		return (scene_print_error(line_num, ERR_PARSE, split[1], strerror(errno)));
	scene->img.ppm = true;
	return (0);
}
