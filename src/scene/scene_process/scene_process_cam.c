#include "miniRT.h"
#include "../scene.h"

int process_cam(t_scene *scene, char **split, int line_num)
{
	t_vec3	look_at;

	if (scene->cam.set == true)
		return (scene_print_error(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (split_count(split) != 4)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (str_to_vec3(split[1], &(scene->cam.pos)) == ERROR)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (str_to_vec3(split[2], &look_at) == ERROR)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	if (vec3_equal(scene->cam.pos, look_at))
		return (scene_print_error(line_num, ERR_PARSE, "cam look-from and look-at cannot be equal", NULL));
	scene->cam.dir = vec3_normalize(vec3_subtract(look_at, scene->cam.pos));
	if (str_to_int(split[3], 1, 179, &(scene->cam.fov)))
		return (scene_print_error(line_num, ERR_PARSE, "Invalid camera FOV (range [1-179])", NULL));
	scene->cam.set = true;
	return (0);
}
