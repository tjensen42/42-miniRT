#include "miniRT.h"
#include "scene.h"

int	scene_setup(t_scene *scene)
{
	int	i;

	scene->img.color = malloc(sizeof(t_color) * scene->img.width * scene->img.height);
	if (scene->img.color == NULL)
		return (ERROR);
	i = 0;
	while (i < THREADS)
	{
		scene->thread[i].num = i;
		scene->thread[i].scene = scene;
		i++;
	}
	scene_img_pos(scene);
	return (0);
}
