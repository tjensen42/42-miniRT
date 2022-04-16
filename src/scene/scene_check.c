#include "miniRT.h"
#include "scene.h"

int	scene_check(t_scene *scene)
{
	if (scene->img.res_set == false)
		return (scene_print_error(-1, ERR_SCENE_INCOM, ERR_MISS_RES, NULL));
	if (scene->sampling.set == false)
		return (scene_print_error(-1, ERR_SCENE_INCOM, ERR_MISS_SAM, NULL));
	if (scene->cam.set == false)
		return (scene_print_error(-1, ERR_SCENE_INCOM, ERR_MISS_CAM, NULL));
	if (scene->bg_set == false)
		return (scene_print_error(-1, ERR_SCENE_INCOM, ERR_MISS_BG, NULL));
	if (scene->amb.set == false)
		return (scene_print_error(-1, ERR_SCENE_INCOM, ERR_MISS_AMB, NULL));
	if (scene->l_obj == NULL)
		return (scene_print_error(-1, ERR_SCENE_INCOM, ERR_MISS_OBJ, NULL));
	return (0);
}
