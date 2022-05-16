#include "mrt_parse.h"

int parse_cam(t_scene *scene, char **split, int line_num)
{
	t_vec3	look_at;

	if (scene->cam.set == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (ft_split_count_str(split) != 4)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (parse_vec3(split[1], &(scene->cam.pos)) == -1)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_vec3(split[2], &look_at) == -1)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	if (vec3_equal(scene->cam.pos, look_at))
		return (print_error_scene(line_num, ERR_PARSE, "cam look-from and look-at cannot be equal", NULL));
	scene->cam.dir = vec3_normalize(vec3_subtract(look_at, scene->cam.pos));
	if (int_from_str(split[3], 1, 179, &(scene->cam.fov)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid camera FOV (range [1-179])", NULL));
	scene->cam.set = true;
	return (0);
}
