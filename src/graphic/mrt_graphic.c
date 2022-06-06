#include "mrt_graphic.h"

void	graphic_loop(void *data);
void	graphic_key_hooks(t_graphic_data *graphic);
void	graphic_render(t_graphic_data *graphic);
void	img_to_mlx_img(t_scene *scene, mlx_image_t *mlx_img);
void	*draw_thread(void *thread_data);

int	graphic(t_scene *scene)
{
	t_graphic_data	gr;

	gr.scene = scene;
	gr.mlx = mlx_init(scene->img.width, scene->img.height, WIN_NAME, false);
	if (gr.mlx == NULL)
		return (-1);
	gr.mlx_img = mlx_new_image(gr.mlx, scene->img.width, scene->img.height);
	if (gr.mlx_img == NULL)
	{
		mlx_terminate(gr.mlx);
		return (-1);
	}
	ft_bzero(gr.mlx_img->pixels, scene->img.width * scene->img.height * sizeof(int));
	mlx_image_to_window(gr.mlx, gr.mlx_img, 0, 0);
	mlx_loop_hook(gr.mlx, &graphic_loop, &gr);
	mlx_loop(gr.mlx);
	mlx_delete_image(gr.mlx, gr.mlx_img);
	mlx_terminate(gr.mlx);
	return (0);
}

void	graphic_loop(void *data)
{
	t_graphic_data	*graphic;

	graphic = data;
	graphic_key_hooks(graphic);
	graphic_render(graphic);
}

void	graphic_key_hooks(t_graphic_data *gr)
{
	if (mlx_is_key_down(gr->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(gr->mlx);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_W))
		move(gr->scene, vec3_add(gr->scene->cam.pos, gr->scene->cam.dir));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_S))
		move(gr->scene, vec3_subtract(gr->scene->cam.pos, gr->scene->cam.dir));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_A))
		move(gr->scene, vec3_subtract(gr->scene->cam.pos, vec3_normalize(gr->scene->img.px)));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_D))
		move(gr->scene, vec3_add(gr->scene->cam.pos, vec3_normalize(gr->scene->img.px)));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_Q))
		move(gr->scene, vec3_subtract(gr->scene->cam.pos, vec3_normalize(gr->scene->img.py)));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_E))
		move(gr->scene, vec3_add(gr->scene->cam.pos, vec3_normalize(gr->scene->img.py)));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_R))
		reset_cam(gr->scene);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_UP))
		rotate_vertical(gr->scene, true);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_DOWN))
		rotate_vertical(gr->scene, false);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_LEFT))
		rotate_horizontal(gr->scene, true);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_RIGHT))
		rotate_horizontal(gr->scene, false);
}
