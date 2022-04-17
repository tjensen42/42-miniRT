#include "miniRT.h"

void	*thread_routine(void *thread_data)
{
	int		y;
	int		x;
	int		samples;
	double	h;
	double	v;
	t_ray	ray;
	struct s_thread_data *thread;
	t_scene *scene;

	thread = thread_data;
	scene = thread->scene;
	ray.pos = thread->scene->cam.pos;
	y = 0;
	while (y < scene->img.height)
	{
		if ((y + THREADS - thread->num) % THREADS == 0)
		{
			v = (double)(scene->img.height - 1 - y + double_random_0_1()) / (scene->img.height - 1); // +-0.5
			x = 0;
			while (x < scene->img.width)
			{
				h = (double)(x + double_random_0_1()) / (scene->img.width - 1);
				ray.dir = vec3_normalize(vec3_subtract(vec3_add(scene->img.pos, vec3_linear_comb(h, scene->img.px, v, scene->img.py)), ray.pos));
				scene->img.color[y * scene->img.width + x] = color_add(scene->img.color[y * scene->img.width + x], trace_bsdf(scene, &ray, 0));
				x++;
			}
		}
		y++;
	}
	return (NULL);
}

int	render_ppm(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		if (pthread_create(&(scene->thread[i].id), NULL, thread_routine, &(scene->thread[i])))
		{
			print_error("pthread_create() failed", strerror(errno), NULL, NULL);
			break ;
		}
		i++;
	}
	i--;
	while (i >= 0)
	{
		if (pthread_join(scene->thread[i].id, NULL))
			print_error("pthread_join() failed", strerror(errno), NULL, NULL);
		i--;
	}
	img_to_ppm(&(scene->img), scene->img.fp_ppm);
	return (0);
}

void	img_to_ppm(struct s_img *img, FILE *fp_ppm)
{
	size_t	i;
	int		color;

	fprintf(fp_ppm, "P3\n");
    fprintf(fp_ppm, "%d %d\n", img->width, img->height);
    fprintf(fp_ppm, "%d\n", 255);
	i = 0;
	while (i < img->width * img->height)
	{
		color = color_to_int(img->color[i]);
		fprintf(fp_ppm, "%3d ", (color >> 16) & 0x0000FF);
		fprintf(fp_ppm, "%3d ", (color >> 8) & 0x0000FF);
		fprintf(fp_ppm, "%3d\n", color & 0x0000FF);
		i++;
	}
}
