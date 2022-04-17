#include "miniRT.h"
#include "scene.h"

int scene_create(t_scene *scene, int argc, char **argv)
{
	ft_memset(scene, 0, sizeof(t_scene));
	if (scene_parser(scene, argc, argv))
		return (ERROR);
	if (scene_check(scene))
		return (ERROR);
	if (scene_setup(scene))
		return (ERROR);
	scene_print(scene);
	return (0);
}

int	scene_destroy(t_scene *scene)
{
	free(scene->img.color);
	if (scene->l_obj)
		ft_lstclear(&(scene->l_obj), free);
	if (scene->l_is)
		ft_lstclear(&(scene->l_is), free);
	if (scene->img.ppm)
		fclose(scene->img.fp_ppm);
	return (0);
}

void scene_img_pos(t_scene *scene)
{
	scene->img.px = vec3_scale(tan((double)scene->cam.fov / 2 * DEG2RAD), vec3_normalize(vec3_vector_product((t_vec3){0, 1, 0}, scene->cam.dir)));
	scene->img.py = vec3_scale(vec3_length(scene->img.px) * scene->img.height / scene->img.width, vec3_normalize(vec3_vector_product(scene->img.px, scene->cam.dir)));
	scene->img.pos = vec3_add(vec3_add(scene->cam.pos, scene->cam.dir), vec3_add(scene->img.px, scene->img.py));
	scene->img.px = vec3_scale(-2.0, scene->img.px);
	scene->img.py = vec3_scale(-2.0, scene->img.py);
}
