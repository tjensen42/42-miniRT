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
	free(scene->img.ptr);
	if (scene->l_obj)
		ft_lstclear(&(scene->l_obj), free);
	if (scene->l_is)
		ft_lstclear(&(scene->l_is), free);
	return (0);
}
