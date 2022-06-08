#include "mrt_graphic.h"

static int	create_join_threads(t_graphic_data *graphic, t_scene *scene);

void	graphic_render(t_graphic_data *graphic)
{
	t_scene	*scene;

	scene = graphic->scene;
	if (scene->sampling.samp == scene->sampling.max_samp)
		return ;
	if (create_join_threads(graphic, scene))
		mlx_close_window(graphic->mlx);
	else
	{
		printf("sample %4d / %4d\n",
			scene->sampling.samp + 1, scene->sampling.max_samp);
		scene->sampling.samp++;
		img_to_mlx_img(scene, graphic->mlx_img);
	}
}

static int	create_join_threads(t_graphic_data *graphic, t_scene *scene)
{
	int		i;
	bool	error;

	error = false;
	i = 0;
	while (i < THREADS)
	{
		scene->thread[i].mlx_img = graphic->mlx_img;
		if (pthread_create(&(scene->thread[i].id), NULL,
				draw_thread, &(scene->thread[i])))
		{
			error = print_error("pthread_create() failed", NULL, NULL, NULL);
			break ;
		}
		i++;
	}
	while (i > 0)
	{
		if (pthread_join(scene->thread[i - 1].id, NULL))
			error = print_error("pthread_join() failed", NULL, NULL, NULL);
		i--;
	}
	return (error);
}

void	*draw_thread(void *thread_data)
{
	int				xy[2];
	t_vec3 			pixel_pos;
	t_ray			ray;
	struct s_img	*img;
	t_thread		*thread;

	thread = thread_data;
	img = &(thread->scene->img);
	ray.pos = thread->scene->cam.pos;
	xy[1] = thread->num;
	while (xy[1] < img->height)
	{
		xy[0] = 0;
		while (xy[0] < img->width)
		{
			pixel_pos = vec3_add(img->pos, vec3_lin_comb(xy[0] + ft_rand_double_0_1(), img->px, img->height - 1 - xy[1] + ft_rand_double_0_1(), img->py));
			ray.dir = vec3_norm(vec3_sub(pixel_pos, ray.pos));
			img->pixel[xy[1] * img->width + xy[0]] = color_add(img->pixel[xy[1] * img->width + xy[0]], trace(thread->scene, &ray, 0));
			xy[0]++;
		}
		xy[1] += THREADS;
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
				color_to_rgba_int(color_scale(1.0 / scene->sampling.samp,
						scene->img.pixel[pixel_pos]),
					scene->sampling.gamma_correction));
			x++;
		}
		y++;
	}
}
