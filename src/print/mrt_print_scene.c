#include "mrt_scene.h"
#include "parse/mrt_parse.h"
#include "print/mrt_print.h"

static void	stats_objects(t_scene *scene);
static void	stats_lights(t_scene *scene);

void	scene_print(t_scene *scene)
{
	printf("%s%-11s %-4d%s   -->   ", COLOR_BL_1, "OBJECTS:",
		ft_lstsize(scene->l_obj), COLOR_NO);
	stats_objects(scene);
	printf("%s%-11s %-4d%s   -->   ", COLOR_CY_1, "LIGHTS:",
		ft_lstsize(scene->l_light), COLOR_NO);
	stats_lights(scene);
	printf("%s%-11s %-4d%s\n", COLOR_BL_1, "TEXTURES:",
		ft_lstsize(scene->l_textures), COLOR_NO);
}

static void	stats_objects(t_scene *scene)
{
	t_list	*iter;
	int		obj_counter[5];

	ft_bzero(obj_counter, sizeof(int) * 5);
	iter = scene->l_obj;
	while (iter)
	{
		if (obj_cont(iter)->print == &print_obj_plane)
			obj_counter[0]++;
		else if (obj_cont(iter)->print == &print_obj_sphere)
			obj_counter[1]++;
		else if (obj_cont(iter)->print == &print_obj_tube)
			obj_counter[2]++;
		else if (obj_cont(iter)->print == &print_obj_disc)
			obj_counter[3]++;
		else if (obj_cont(iter)->print == &print_obj_rectangle)
			obj_counter[4]++;
		iter = iter->next;
	}
	printf("%s%-11s %-4d   ", COLOR_BL, "PLANES:", obj_counter[0]);
	printf("%-11s %-4d   ", "SPHERES:", obj_counter[1]);
	printf("%-11s %-4d   ", "TUBES:", obj_counter[2]);
	printf("%-11s %-4d   ", "DISCS:", obj_counter[3]);
	printf("%-11s %-4d%s\n", "RECTANGLES:", obj_counter[4], COLOR_NO);
}

static void	stats_lights(t_scene *scene)
{
	t_list	*iter;
	int		light_counter[3];

	ft_bzero(light_counter, sizeof(int) * 3);
	iter = scene->l_light;
	while (iter)
	{
		if (light_cont(iter)->print == &print_light_sphere)
			light_counter[0]++;
		else if (light_cont(iter)->print == &print_light_disc)
			light_counter[1]++;
		else if (light_cont(iter)->print == &print_light_rectangle)
			light_counter[2]++;
		iter = iter->next;
	}
	printf("%s%-11s %-4d   ", COLOR_CY, "SPHERES:", light_counter[0]);
	printf("%-11s %-4d   ", "DISCS:", light_counter[1]);
	printf("%-11s %-4d%s\n", "RECTANGLE:", light_counter[2], COLOR_NO);
}
