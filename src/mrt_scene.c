#include "mrt_scene.h"
#include "parse/mrt_parse.h"
#include "print/mrt_print.h"

static int	scene_setup(t_scene *scene);
static int	scene_check(t_scene *scene);
int			scene_norm_light_weights(t_list *l_light);

int	scene_create(t_scene *scene, const char *file)
{
	ft_bzero(scene, sizeof(t_scene));
	printf("%sPARSING FILE: %s%s\n", COLOR_GR_1, file, COLOR_NO);
	if (parse_scene(scene, file))
		return (-1);
	if (scene_check(scene))
		return (-1);
	if (scene_setup(scene))
		return (-1);
	scene_print(scene);
	return (0);
}

void	scene_destroy(t_scene *scene)
{
	free(scene->img.pixel);
	ft_lstclear(&(scene->l_obj), free);
	ft_lstclear(&(scene->l_light), free);
	ft_lstclear(&(scene->l_textures), c_texture_destroy);
}

static int	scene_check(t_scene *scene)
{
	if (scene->img.res_set == false)
		return (print_error_scene(-1, ERR_PARSE, ERR_SCENE_INCOM, ERR_MISS_RES));
	if (scene->sampling.set == false)
		return (print_error_scene(-1, ERR_PARSE, ERR_SCENE_INCOM, ERR_MISS_SAM));
	if (scene->bg.set == false)
		return (print_error_scene(-1, ERR_PARSE, ERR_SCENE_INCOM, ERR_MISS_BG));
	if (scene->amb.set == false)
		return (print_error_scene(-1, ERR_PARSE, ERR_SCENE_INCOM, ERR_MISS_AMB));
	if (scene->cam.set == false)
		return (print_error_scene(-1, ERR_PARSE, ERR_SCENE_INCOM, ERR_MISS_CAM));
	if (scene->l_obj == NULL)
		return (print_error_scene(-1, ERR_PARSE, ERR_SCENE_INCOM, ERR_MISS_OBJ));
	return (0);
}

static int	scene_setup(t_scene *scene)
{
	int	i;

	scene->img.pixel = malloc(scene->img.width * scene->img.height
			* sizeof(t_color));
	if (scene->img.pixel == NULL)
		return (-1);
	ft_bzero(scene->img.pixel, scene->img.width * scene->img.height
		* sizeof(t_color));
	i = 0;
	while (i < THREADS)
	{
		scene->thread[i].num = i;
		scene->thread[i].scene = scene;
		i++;
	}
	if (scene->l_light == NULL)
	{
		scene->sampling.cosine = 1.0;
		scene->sampling.light = 0.0;
	}
	scene_norm_light_weights(scene->l_light);
	scene_calc_img_pos(scene);
	return (0);
}
