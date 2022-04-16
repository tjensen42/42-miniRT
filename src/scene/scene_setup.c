#include "miniRT.h"
#include "scene.h"

int	scene_setup(t_scene *scene)
{
	scene->img.ptr = malloc(sizeof(t_color) * scene->img.width * scene->img.height);
	if (scene->img.ptr == NULL)
		return (ERROR);
	return (0);
}
