#include "mrt_graphic.h"

void	graphic_render(t_graphic_data *graphic)
{
	int		i;
	t_scene	*scene;

	scene = graphic->scene;
	if (scene->sampling.samp == scene->sampling.max_samp)
		return ;
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
	printf("sample %d / %d\n", scene->sampling.samp + 1, scene->sampling.max_samp);
	scene->sampling.samp++;
	img_to_mlx_img(scene, graphic->mlx_img);
}

void	*draw_thread(void *thread_data)
{
	int				y;
	int				x;
	t_vec3 			pixel_pos;
	t_ray			ray;
	struct s_img	*img;
	t_thread		*thread;

	thread = thread_data;
	img = &(thread->scene->img);
	ray.pos = thread->scene->cam.pos;
	y = thread->num;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			pixel_pos = vec3_add(img->pos, vec3_linear_comb(x + ft_rand_double_0_1(), img->px, img->height - 1 - y + ft_rand_double_0_1(), img->py));
			ray.dir = vec3_normalize(vec3_subtract(pixel_pos, ray.pos));
			img->pixel[y * img->width + x] = color_add(img->pixel[y * img->width + x], trace(thread->scene, &ray, 0));
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
					color_to_rgba_int(color_scale(1.0 / scene->sampling.samp,
							scene->img.pixel[pixel_pos]), scene->sampling.gamma_correction));
			x++;
		}
		y++;
	}
}
