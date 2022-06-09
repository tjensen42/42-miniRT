/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_graphic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:55:42 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 18:06:28 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_graphic.h"
#include "print/mrt_print.h"

static void	graphic_loop(void *data);
static void	graphic_key_hooks(t_graphic_data *gr);
static void	graphic_key_hooks_move(t_graphic_data *gr);
static void	graphic_key_hooks_rotate(t_graphic_data *gr);

int	graphic(t_scene *scene)
{
	t_graphic_data	gr;

	printf("%s\nRENDERING SCENE:%s\n", COLOR_GR_1, COLOR_NO);
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
	ft_bzero(gr.mlx_img->pixels, scene->img.width * scene->img.height
		* sizeof(int));
	mlx_image_to_window(gr.mlx, gr.mlx_img, 0, 0);
	mlx_loop_hook(gr.mlx, &graphic_loop, &gr);
	mlx_loop(gr.mlx);
	printf("\n");
	mlx_delete_image(gr.mlx, gr.mlx_img);
	mlx_terminate(gr.mlx);
	return (0);
}

static void	graphic_loop(void *data)
{
	t_graphic_data	*graphic;

	graphic = data;
	graphic_key_hooks(graphic);
	graphic_render(graphic);
}

static void	graphic_key_hooks(t_graphic_data *gr)
{
	if (mlx_is_key_down(gr->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(gr->mlx);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_R))
		reset_cam(gr->scene);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_P))
		print_scene_debug(gr->scene);
	graphic_key_hooks_move(gr);
	graphic_key_hooks_rotate(gr);
}

static void	graphic_key_hooks_move(t_graphic_data *gr)
{
	bool			shift;
	double			scale;
	struct s_cam	*cam;

	shift = (mlx_is_key_down(gr->mlx, MLX_KEY_LEFT_SHIFT)
			|| mlx_is_key_down(gr->mlx, MLX_KEY_RIGHT_SHIFT));
	scale = 1.0 - (0.8 * shift);
	cam = &(gr->scene->cam);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_W))
		move(gr->scene, vec3_add(cam->pos, vec3_scale(scale, cam->dir)));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_S))
		move(gr->scene, vec3_sub(cam->pos, vec3_scale(scale, cam->dir)));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_A))
		move(gr->scene, vec3_sub(cam->pos,
				vec3_scale(scale, vec3_norm(gr->scene->img.px))));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_D))
		move(gr->scene, vec3_add(cam->pos,
				vec3_scale(scale, vec3_norm(gr->scene->img.px))));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_Q))
		move(gr->scene, vec3_sub(cam->pos,
				vec3_scale(scale, vec3_norm(gr->scene->img.py))));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_E))
		move(gr->scene, vec3_add(cam->pos,
				vec3_scale(scale, vec3_norm(gr->scene->img.py))));
}

static void	graphic_key_hooks_rotate(t_graphic_data *gr)
{
	bool	shift;

	shift = (mlx_is_key_down(gr->mlx, MLX_KEY_LEFT_SHIFT)
			|| mlx_is_key_down(gr->mlx, MLX_KEY_RIGHT_SHIFT));
	if (mlx_is_key_down(gr->mlx, MLX_KEY_UP))
		rotate_vertical(gr->scene, true, 10.0 - 9.0 * shift);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_DOWN))
		rotate_vertical(gr->scene, false, -10.0 + 9.0 * shift);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_LEFT))
		rotate_horizontal(gr->scene, 10.0 - 9.0 * shift);
	if (mlx_is_key_down(gr->mlx, MLX_KEY_RIGHT))
		rotate_horizontal(gr->scene, -10.0 + 9.0 * shift);
}
