#include "mrt_graphic.h"

void	rotate_horizontal(t_scene *scene, bool right)
{
	double	sine;
	double	cosine;
	double	tmp;

	if (right == true)
		sine = sin(10.0 * DEG2RAD);
	else
		sine = sin(-10.0 * DEG2RAD);
	cosine = cos(10.0 * DEG2RAD);
	tmp = cosine * scene->cam.dir.x + sine * scene->cam.dir.z;
	scene->cam.dir.z = - sine * scene->cam.dir.x + cosine * scene->cam.dir.z;
	scene->cam.dir.x = tmp;
	scene->cam.dir = vec3_normalize(scene->cam.dir);
	tmp = cosine * scene->img.qx.x + sine * scene->img.qx.z;
	scene->img.qx.z = - sine * scene->img.qx.x + cosine * scene->img.qx.z;
	scene->img.qx.x = tmp;
	tmp = cosine * scene->img.qy.x + sine * scene->img.qy.z;
	scene->img.qy.z = - sine * scene->img.qy.x + cosine * scene->img.qy.z;
	scene->img.qy.x = tmp;
	scene->img.px = vec3_scale(-2.0 / (scene->img.width - 1), scene->img.qx);
	scene->img.py = vec3_scale(-2.0 / (scene->img.height - 1), scene->img.qy);
	scene->img.pos = vec3_add(vec3_add(scene->cam.pos, scene->cam.dir), vec3_add(scene->img.qx, scene->img.qy));
	print_vec3(scene->cam.pos, "cam_pos", COLOR_BL);
	print_vec3(scene->cam.dir, "cam_dir", COLOR_CY);
	reset_sampling(scene);
}

void	rotate_vertical(t_scene *scene, bool up)
{
	if (up == true)
	{
		if (scene->cam.dir.y > 1.0 - 1e-4)
			return ;
		else if (vec3_scalar_product(scene->cam.dir, (t_vec3){0.0, 1.0, 0.0}) <= cos(10.0 * DEG2RAD))
			scene->cam.dir = vec3_add(scene->cam.dir, vec3_scale(sin(10.0 * DEG2RAD), vec3_normalize(scene->img.py)));
		else
			scene->cam.dir = (t_vec3){0.0, 1.0, 0.0};
	}
	else
	{
		if (scene->cam.dir.y < -1.0 + 1e-4)
			return ;
		else if (vec3_scalar_product(scene->cam.dir, (t_vec3){0.0, 1.0, 0.0}) >= cos(170.0 * DEG2RAD))
			scene->cam.dir = vec3_add(scene->cam.dir, vec3_scale(-sin(10.0 * DEG2RAD), vec3_normalize(scene->img.py)));
		else
			scene->cam.dir = (t_vec3){0.0, -1.0, 0.0};
	}
	scene->cam.dir = vec3_normalize(scene->cam.dir);
	scene->img.qy = vec3_scale(vec3_length(scene->img.qx) * scene->img.height / scene->img.width, vec3_normalize(vec3_vector_product(scene->img.qx, scene->cam.dir)));
	scene->img.py = vec3_scale(-2.0 / (scene->img.height - 1), scene->img.qy);
	scene->img.pos = vec3_add(vec3_add(scene->cam.pos, scene->cam.dir), vec3_add(scene->img.qx, scene->img.qy));
	print_vec3(scene->cam.pos, "cam_pos", COLOR_BL);
	print_vec3(scene->cam.dir, "cam_dir", COLOR_CY);
	reset_sampling(scene);
}
