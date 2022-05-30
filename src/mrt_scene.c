#include "mrt_scene.h"
#include "parse/mrt_parse.h"
#include "print/mrt_print.h"

static int	scene_setup(t_scene *scene);
static int	scene_check(t_scene *scene);
int			scene_check_is_weights(t_list *l_light);

int scene_create(t_scene *scene, const char *file)
{
	ft_bzero(scene, sizeof(t_scene));
	if (parse_scene(scene, file))
		return (-1);
	if (scene_check(scene))
		return (-1);
	if (scene_setup(scene))
		return (-1);
	print_scene(scene);
	return (0);
}

int	scene_destroy(t_scene *scene)
{
	free(scene->img.pixel);
	if (scene->l_obj)
		ft_lstclear(&(scene->l_obj), free);
	if (scene->l_light)
		ft_lstclear(&(scene->l_light), free);
	if (scene->img.ppm)
		fclose(scene->img.fp_ppm);
	return (0);
}

static int	scene_check(t_scene *scene)
{
	if (scene->img.res_set == false)
		return (print_error_scene(-1, ERR_SCENE_INCOM, ERR_MISS_RES, NULL));
	if (scene->sampling.set == false)
		return (print_error_scene(-1, ERR_SCENE_INCOM, ERR_MISS_SAM, NULL));
	if (scene->cam.set == false)
		return (print_error_scene(-1, ERR_SCENE_INCOM, ERR_MISS_CAM, NULL));
	if (scene->bg.set == false)
		return (print_error_scene(-1, ERR_SCENE_INCOM, ERR_MISS_BG, NULL));
	if (scene->amb.set == false)
		return (print_error_scene(-1, ERR_SCENE_INCOM, ERR_MISS_AMB, NULL));
	if (scene->l_obj == NULL)
		return (print_error_scene(-1, ERR_SCENE_INCOM, ERR_MISS_OBJ, NULL));
	if (scene_check_is_weights(scene->l_light))
		return (print_error_scene(-1, ERR_SCENE_INCOM, "Invalid is-weight sum", NULL));
	return (0);
}

static int	scene_setup(t_scene *scene)
{
	int	i;

	scene->img.pixel = malloc(sizeof(t_color) * scene->img.width * scene->img.height);
	if (scene->img.pixel == NULL)
		return (-1);
	ft_bzero(scene->img.pixel, sizeof(t_color) * scene->img.width * scene->img.height);
	i = 0;
	while (i < THREADS)
	{
		scene->thread[i].num = i;
		scene->thread[i].scene = scene;
		i++;
	}
	scene_calc_img_pos(scene);
	return (0);
}

int scene_check_is_weights(t_list *l_light)
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

// void	scene_calc_img_pos(t_scene *scene, bool update_px)
// {
// 	if (update_px)
// 	{
// 		if (fabs(scene->cam.dir.y) > 1.0 - 1e-4)
// 			scene->img.qx = vec3_scale(tan((double)scene->cam.fov / 2.0 * DEG2RAD), vec3_normalize(vec3_vector_product((t_vec3){1, 0, 0}, scene->cam.dir)));
// 		else
// 			scene->img.qx = vec3_scale(tan((double)scene->cam.fov / 2.0 * DEG2RAD), vec3_normalize(vec3_vector_product((t_vec3){0, 1, 0}, scene->cam.dir)));
// 		scene->img.px = vec3_scale(-2.0 / (scene->img.width - 1), scene->img.qx);
// 	}
// 	scene->img.qy = vec3_scale(vec3_length(scene->img.qx) * scene->img.height / scene->img.width, vec3_normalize(vec3_vector_product(scene->img.qx, scene->cam.dir)));
// 	scene->img.pos = vec3_add(vec3_add(scene->cam.pos, scene->cam.dir), vec3_add(scene->img.qx, scene->img.qy));
// 	scene->img.py = vec3_scale(-2.0 / (scene->img.height - 1), scene->img.qy);
// }

void	scene_calc_img_pos(t_scene *scene)
{
	if (fabs(scene->cam.dir.y) > 1.0 - 1e-4)
		scene->img.qx = vec3_scale(tan((double)scene->cam.fov / 2.0 * DEG2RAD), vec3_normalize(vec3_vector_product((t_vec3){1, 0, 0}, scene->cam.dir)));
	else
		scene->img.qx = vec3_scale(tan((double)scene->cam.fov / 2.0 * DEG2RAD), vec3_normalize(vec3_vector_product((t_vec3){0, 1, 0}, scene->cam.dir)));
	scene->img.qy = vec3_scale(vec3_length(scene->img.qx) * scene->img.height / scene->img.width, vec3_normalize(vec3_vector_product(scene->img.qx, scene->cam.dir)));
	scene->img.px = vec3_scale(-2.0 / (scene->img.width - 1), scene->img.qx);
	scene->img.py = vec3_scale(-2.0 / (scene->img.height - 1), scene->img.qy);
	scene->img.pos = vec3_add(vec3_add(scene->cam.pos, scene->cam.dir), vec3_add(scene->img.qx, scene->img.qy));
}