#include "miniRT.h"
#include "graphic/mrt_graphic.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2 || !argv[1])
	{
		print_error(ERR_USAGE, NULL, NULL, NULL);
		return (1);
	}
	srand(time(NULL));
	if (scene_create(&scene, argv[1]))
	{
		scene_destroy(&scene);
		return (2);
	}
	graphic(&scene);
	scene_destroy(&scene);
	return (0);
}
