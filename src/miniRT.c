#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	srand(time(NULL));
	if (scene_create(&scene, argc, argv) == ERROR)
	{
		scene_destroy(&scene);
		return (EXIT_FAILURE);
	}
	// if (scene.img.ppm)
	// 	render_to_ppm();
	// else
	// {
	// 	mlx_setup():
	// 	mlx_loop_hook():
	// 	mlx_loop():
	// }
	scene_destroy(&scene);
	return (EXIT_SUCCESS);
}

double double_random_0_1(void)
{
	return (rand() / (double)(RAND_MAX));
}

int	print_error(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s3, STDERR_FILENO);
	}
	if (s4)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s4, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (ERROR);
}
