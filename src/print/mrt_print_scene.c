#include "mrt_print.h"

static void	print_scene_img(struct s_img *img);
static void	print_scene_specs(t_scene *scene);

int	print_scene(t_scene *scene)
{
	t_list *iter;

	print_scene_specs(scene);
	iter = scene->l_obj;
	while (iter)
	{
		obj_cont(iter)->print(iter);
		iter = iter->next;
	}
	iter = scene->l_is;
	while (iter)
	{
		// is_cont(iter)->print(iter);
		iter = iter->next;
	}
	return (0);
}

static void	print_scene_specs(t_scene *scene)
{
	print_scene_img(&(scene->img));
	printf("COUNTER:\n");
	print_scene_int(ft_lstsize(scene->l_obj), "objects:", NULL);
	print_scene_int(ft_lstsize(scene->l_is), "oversampl:", NULL);
	printf("SAMPLING:\n");
	print_scene_int(scene->sampling.max_samp, "samples:", NULL);
	print_scene_int(scene->sampling.recursion_depth, "rec_depth:", NULL);
	print_scene_double(scene->sampling.cosine_samp, "cosine:", NULL);
	print_scene_double(scene->sampling.import_samp, "import:", NULL);
	printf("\n");
	printf("CAMERA:\n");
	print_vec3(scene->cam.pos, "pos:", COLOR_BL);
	print_vec3(scene->cam.dir, "dir:", COLOR_CY);
	print_scene_int(scene->cam.fov, "fov:", NULL);
	printf("\n");
	printf("BACKGROUND:\n");
	print_color(scene->bg.color[0]);
	print_color(scene->bg.color[1]);
	printf("\n");
	printf("AMBIENT:\n");
	print_color(scene->amb.color);
	print_scene_double(scene->amb.brightness, "bright", NULL);
	printf("\n");
}

static void	print_scene_img(struct s_img *img)
{
	printf("IMAGE:\n");
	if (img->ppm)
		printf("\t%-10s %8s\n", "ppm:", "true");
	else
		printf("\t%-10s %8s\n", "ppm:", "false");
	print_scene_int(img->width, "width:", NULL);
	print_scene_int(img->height, "height:", NULL);
	print_vec3(img->pos, "img-pos:", COLOR_BL);
	print_vec3(img->px, "img-x:", COLOR_CY);
	print_vec3(img->py, "img-y:", COLOR_CY);
	printf("\n");
}

void	print_scene_int(int num, const char *str, const char *color)
{
	if (color)
		printf("\t%s%-10s %8d%s\n", color, str, num, COLOR_NO);
	else
		printf("\t%-10s %8d\n", str, num);
}

void	print_scene_double(double num, const char *str, const char *color)
{
	if (color)
		printf("\t%s%-10s %8.3f%s\n", color, str, num, COLOR_NO);
	else
		printf("\t%-10s %8.3f\n", str, num);
}
