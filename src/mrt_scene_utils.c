#include "mrt_scene.h"
#include "parse/mrt_parse.h"
#include "print/mrt_print.h"

int	scene_check_light_weights(t_list *l_light)
{
	t_list	*iter;
	double	weight_sum;

	if (l_light == NULL)
		return (0);
	weight_sum = 0;
	iter = l_light;
	while (iter)
	{
		weight_sum += light_cont(iter)->weight;
		iter = iter->next;
	}
	if (weight_sum <= 0)
		return (-1);
	iter = l_light;
	while (iter)
	{
		light_cont(iter)->weight /= weight_sum;
		iter = iter->next;
	}
	return (0);
}

void	scene_calc_img_pos(t_scene *scene)
{
	if (fabs(scene->cam.dir.y) > 1.0 - 1e-4)
		scene->img.qx = vec3_scale(tan((double)scene->cam.fov / 2.0 * DEG2RAD),
				vec3_normalize(
					vec3_vector_product((t_vec3){0, 0, -1.0},
						scene->cam.dir)));
	else
		scene->img.qx = vec3_scale(tan((double)scene->cam.fov / 2.0 * DEG2RAD),
				vec3_normalize(
					vec3_vector_product((t_vec3){0, 1.0, 0},
						scene->cam.dir)));
	scene->img.qy = vec3_scale(vec3_length(scene->img.qx)
			* scene->img.height / scene->img.width,
			vec3_normalize(vec3_vector_product(scene->img.qx,
					scene->cam.dir)));
	scene->img.px = vec3_scale(-2.0 / (scene->img.width - 1), scene->img.qx);
	scene->img.py = vec3_scale(-2.0 / (scene->img.height - 1), scene->img.qy);
	scene->img.pos = vec3_add(vec3_add(scene->cam.pos, scene->cam.dir),
			vec3_add(scene->img.qx, scene->img.qy));
}
