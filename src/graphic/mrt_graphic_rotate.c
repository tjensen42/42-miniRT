#include "mrt_graphic.h"

static bool	cam_dir_up(struct s_cam *cam, t_vec3 img_py, double rot);
static bool	cam_dir_down(struct s_cam *cam, t_vec3 img_py, double rot);

void	rotate_horizontal(t_scene *scene, double rot)
{
	double	sine;
	double	cosine;
	double	tmp;

	sine = sin(rot * DEG2RAD);
	cosine = cos(rot * DEG2RAD);
	tmp = cosine * scene->cam.dir.x + sine * scene->cam.dir.z;
	scene->cam.dir.z = -sine * scene->cam.dir.x + cosine * scene->cam.dir.z;
	scene->cam.dir.x = tmp;
	scene->cam.dir = vec3_norm(scene->cam.dir);
	tmp = cosine * scene->img.qx.x + sine * scene->img.qx.z;
	scene->img.qx.z = -sine * scene->img.qx.x + cosine * scene->img.qx.z;
	scene->img.qx.x = tmp;
	tmp = cosine * scene->img.qy.x + sine * scene->img.qy.z;
	scene->img.qy.z = -sine * scene->img.qy.x + cosine * scene->img.qy.z;
	scene->img.qy.x = tmp;
	scene->img.px = vec3_scale(-2.0 / (scene->img.width - 1), scene->img.qx);
	scene->img.py = vec3_scale(-2.0 / (scene->img.height - 1), scene->img.qy);
	scene->img.pos = vec3_add(vec3_add(scene->cam.pos, scene->cam.dir),
			vec3_add(scene->img.qx, scene->img.qy));
	reset_sampling(scene);
}

void	rotate_vertical(t_scene *scene, bool up, double rot)
{
	if ((up && cam_dir_up(&(scene->cam), scene->img.py, rot))
		|| (!up && cam_dir_down(&(scene->cam), scene->img.py, rot)))
	{
		scene->img.qy = vec3_scale(
				vec3_len(scene->img.qx)
				* scene->img.height / scene->img.width,
				vec3_norm(
					vec3_cross(scene->img.qx, scene->cam.dir)));
		scene->img.py = vec3_scale(-2.0 / (scene->img.height - 1),
				scene->img.qy);
		scene->img.pos = vec3_add(vec3_add(scene->cam.pos, scene->cam.dir),
				vec3_add(scene->img.qx, scene->img.qy));
		reset_sampling(scene);
	}
}

static bool	cam_dir_up(struct s_cam *cam, t_vec3 img_py, double rot)
{
	double	cosine;

	cosine = vec3_dot(cam->dir, (t_vec3){0.0, 1.0, 0.0});
	if (cam->dir.y > 1.0 - 1e-4)
		return (false);
	else if (cosine <= cos(rot * DEG2RAD))
		cam->dir = vec3_add(cam->dir, vec3_scale(sin(rot * DEG2RAD),
					vec3_norm(img_py)));
	else
		cam->dir = (t_vec3){0.0, 1.0, 0.0};
	cam->dir = vec3_norm(cam->dir);
	return (true);
}

static bool	cam_dir_down(struct s_cam *cam, t_vec3 img_py, double rot)
{
	double	cosine;

	cosine = vec3_dot(cam->dir, (t_vec3){0.0, 1.0, 0.0});
	if (cam->dir.y < -1.0 + 1e-4)
		return (false);
	else if (cosine >= cos((180.0 + rot) * DEG2RAD))
		cam->dir = vec3_add(cam->dir, vec3_scale(sin(rot * DEG2RAD),
					vec3_norm(img_py)));
	else
		cam->dir = (t_vec3){0.0, -1.0, 0.0};
	return (true);
}
