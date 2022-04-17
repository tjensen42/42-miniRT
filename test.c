// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/time.h>

// int	main(int argc, char *argv[])
// {
// 	srand(time(NULL));
// 	while (1)
// 	{
// 		printf("%f\n", (double)rand() / RAND_MAX);
// 		fflush(stdout);
// 	}

// }


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 00:40:08 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/31 00:41:56 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/tjensen/Documents/code/42-miniRT-new/lib/libmlx/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#define WIDTH 1920
#define HEIGHT 1080

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

int32_t	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 100, 100);
	g_img = mlx_new_image(mlx, 100, 100);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
