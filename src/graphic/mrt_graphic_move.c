#include "mrt_graphic.h"

void	move(t_scene *scene, t_vec3 new_pos)
{
	scene->cam.pos = new_pos;
	scene->img.pos = vec3_add(vec3_add(scene->cam.pos, scene->cam.dir),
						vec3_add(scene->img.qx, scene->img.qy));
	print_vec3(scene->cam.pos, "cam_pos", COLOR_BL);
	print_vec3(scene->cam.dir, "cam_dir", COLOR_CY);
	reset_sampling(scene);
}

void	reset_cam(t_scene *scene)
{
	scene->cam.pos = scene->cam.pos_initial;
	scene->cam.dir = scene->cam.dir_initial;
	scene_calc_img_pos(scene);
	print_vec3(scene->cam.pos, "cam_pos", COLOR_BL);
	print_vec3(scene->cam.dir, "cam_dir", COLOR_CY);
	reset_sampling(scene);
}

void	reset_sampling(t_scene *scene)
{
	scene->sampling.samp = 0;
	ft_bzero(scene->img.pixel, scene->img.width
		* scene->img.height * sizeof(t_color));
}
