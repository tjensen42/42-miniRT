#include "mrt_graphic.h"

void	graphic_loop(void *data);
void	graphic_key_hooks(t_graphic_data *graphic);
void	graphic_render(t_graphic_data *graphic);
void	img_to_mlx_img(t_scene *scene, mlx_image_t *mlx_img);
void	*draw_thread(void *thread_data);

int	graphic(t_scene *scene)
{
	t_graphic_data	graphic;

	graphic.scene = scene;
	graphic.mlx = mlx_init(scene->img.width, scene->img.height, WIN_NAME, true);
	if (graphic.mlx == NULL)
		return (-1);
	graphic.mlx_img = mlx_new_image(graphic.mlx, scene->img.width, scene->img.height);
	if (graphic.mlx_img == NULL)
	{
		mlx_terminate(graphic.mlx);
		return (-1);
	}
	ft_bzero(graphic.mlx_img->pixels, scene->img.width * scene->img.height * sizeof(int));
	mlx_image_to_window(graphic.mlx, graphic.mlx_img, 0, 0);
	mlx_loop_hook(graphic.mlx, &graphic_loop, &graphic);
	mlx_loop(graphic.mlx);
	mlx_terminate(graphic.mlx);
	return (0);
}

void	graphic_loop(void *data)
{
	t_graphic_data	*graphic;

	graphic = data;
	graphic_key_hooks(graphic);
	graphic_render(graphic);
}

void	move(t_scene *scene, t_vec3 new_pos)
{
	scene->cam.pos = new_pos;
	scene->sampling.samp = 0;
	ft_bzero(scene->img.pixel, sizeof(t_color) * scene->img.width * scene->img.height);
	scene_calc_img_pos(scene);
}

void	rotate(t_scene *scene, t_vec3 new_dir)
{
	scene->cam.dir = new_dir;
	scene->sampling.samp = 0;
	ft_bzero(scene->img.pixel, sizeof(t_color) * scene->img.width * scene->img.height);
	scene_calc_img_pos(scene);
}

void	graphic_key_hooks(t_graphic_data *graphic)
{
	if (mlx_is_key_down(graphic->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(graphic->mlx);
	if (mlx_is_key_down(graphic->mlx, MLX_KEY_W))
		move(graphic->scene, vec3_add(graphic->scene->cam.pos, graphic->scene->cam.dir));
	if (mlx_is_key_down(graphic->mlx, MLX_KEY_S))
		move(graphic->scene, vec3_subtract(graphic->scene->cam.pos, graphic->scene->cam.dir));
	if (mlx_is_key_down(graphic->mlx, MLX_KEY_A))
		move(graphic->scene, vec3_subtract(graphic->scene->cam.pos, vec3_normalize(graphic->scene->img.px)));
	if (mlx_is_key_down(graphic->mlx, MLX_KEY_D))
		move(graphic->scene, vec3_add(graphic->scene->cam.pos, vec3_normalize(graphic->scene->img.px)));
	if (mlx_is_key_down(graphic->mlx, MLX_KEY_Q))
		move(graphic->scene, vec3_subtract(graphic->scene->cam.pos, vec3_normalize(graphic->scene->img.py)));
	if (mlx_is_key_down(graphic->mlx, MLX_KEY_E))
		move(graphic->scene, vec3_add(graphic->scene->cam.pos, vec3_normalize(graphic->scene->img.py)));
	if (mlx_is_mouse_down(graphic->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		int mouse_x, mouse_y;
		mlx_get_mouse_pos(graphic->mlx, &mouse_x, &mouse_y);
		if (mouse_x < graphic->scene->img.width / 2)
		{
			double sine, cosine;
			sine = sin(-10 * DEG2RAD);
			cosine = cos(10 * DEG2RAD);
			rotate(graphic->scene,
				(t_vec3){cosine * graphic->scene->cam.dir.x - sine * graphic->scene->cam.dir.z,
						graphic->scene->cam.dir.y,
						sine * graphic->scene->cam.dir.x + cosine * graphic->scene->cam.dir.z});
		}
		else
		{
			double sine, cosine;
			sine = sin(10 * DEG2RAD);
			cosine = cos(10 * DEG2RAD);
			rotate(graphic->scene,
				(t_vec3){cosine * graphic->scene->cam.dir.x - sine * graphic->scene->cam.dir.z,
						graphic->scene->cam.dir.y,
						sine * graphic->scene->cam.dir.x + cosine * graphic->scene->cam.dir.z});
		}
	}
	if (mlx_is_mouse_down(graphic->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		int mouse_x, mouse_y;
		mlx_get_mouse_pos(graphic->mlx, &mouse_x, &mouse_y);
		if (mouse_y < graphic->scene->img.height / 2)
		{
			graphic->scene->cam.dir.y += 0.1;
			graphic->scene->cam.dir = vec3_normalize(graphic->scene->cam.dir);
			rotate(graphic->scene, graphic->scene->cam.dir);
		}
		else
		{
			graphic->scene->cam.dir.y -= 0.1;
			graphic->scene->cam.dir = vec3_normalize(graphic->scene->cam.dir);
			rotate(graphic->scene, graphic->scene->cam.dir);
		}
	}
}

void	graphic_render(t_graphic_data *graphic)
{
	int			i;
	t_scene		*scene;

	scene = graphic->scene;
	if (scene->sampling.samp == scene->sampling.max_samp)
		return ;
	printf("sample %d / %d\n", scene->sampling.samp + 1, scene->sampling.max_samp);
	i = 0;
	while (i < THREADS)
	{
		scene->thread[i].mlx_img = graphic->mlx_img;
		if (pthread_create(&(scene->thread[i].id), NULL, draw_thread, &(scene->thread[i])))
		{
			print_error("Error\n", "pthread_create() failed", NULL, NULL);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		if (pthread_join(scene->thread[i].id, NULL))
			print_error("Error\n", "pthread_join() failed", NULL, NULL);
		i++;
	}
	scene->sampling.samp++;
	img_to_mlx_img(scene, graphic->mlx_img);
}

void	*draw_thread(void *thread_data)
{
	int			y;
	int			x;
	t_vec3 		pixel_pos;
	t_ray		ray;
	t_scene		*scene;
	t_thread	*thread;

	thread = thread_data;
	scene = thread->scene;
	ray.pos = scene->cam.pos;
	y = thread->num;
	while (y < scene->img.height)
	{
		x = 0;
		while (x < scene->img.width)
		{
			pixel_pos = vec3_add(scene->img.pos, vec3_linear_comb(x + ft_rand_double_0_1(), scene->img.px, scene->img.height - 1 - y + ft_rand_double_0_1(), scene->img.py));
			ray.dir = vec3_normalize(vec3_subtract(pixel_pos, ray.pos));
			scene->img.pixel[y * scene->img.width + x] = color_add(scene->img.pixel[y * scene->img.width + x], trace(thread->scene, &ray, 0));
			// scene->img.pixel[y * scene->img.width + x] = (t_color){0.5 / (thread->num + 1.0), 1.0 / (thread->num + 1.0), 0.2 / (thread->num + 1.0)};
			x++;
		}
		y += THREADS;
	}
	return (NULL);
}

void	img_to_mlx_img(t_scene *scene, mlx_image_t *mlx_img)
{
	size_t		x;
	size_t		y;
	size_t		pixel_pos;
	uint8_t		*mlx_pixel;

	mlx_pixel = mlx_img->pixels;
	y = 0;
	while (y < mlx_img->height)
	{
		x = 0;
		while (x < mlx_img->width)
		{
			pixel_pos = y * mlx_img->width + x;
			mlx_put_pixel(mlx_img, x, y,
					color_to_rgba_int(color_scale(1.0 / scene->sampling.samp, scene->img.pixel[pixel_pos])));
			x++;
		}
		y++;
	}
}
