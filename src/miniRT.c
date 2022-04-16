#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (scene_create(&scene, argc, argv) == ERROR)
	{
		scene_destroy(&scene);
		return (EXIT_FAILURE);
	}
	scene_destroy(&scene);
	return (EXIT_SUCCESS);
}
