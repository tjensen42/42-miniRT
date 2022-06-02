#include "mrt_parse.h"
#include "print/mrt_print.h"
#include "trace/mrt_trace.h"

#include "lib/libmlx/include/MLX42/MLX42.h"

int	convert_mlx_texture_to_color(mlx_texture_t *mlx_texture, t_texture *c_texture);

int	parse_texture(t_scene *scene, char **split, int line_num)
{
	t_list			*texture;
	t_texture		*c_texture;
	mlx_texture_t	*mlx_texture;

	if (ft_split_count_str(split) != 3)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	// parse name cb error
	texture = texture_new();
	if (texture == NULL)
		return (-1);
	ft_lstadd_back(&scene->l_textures, texture);
	c_texture = texture->content;
	c_texture->name = ft_strdup(split[1]);
	mlx_texture = mlx_load_png(split[2]);
	if (mlx_texture == NULL)
	{
		return (print_error_scene(line_num, ERR_PARSE, "Cannot load png", split[2]));
		return (-1);
	}
	c_texture->width = mlx_texture->width;
	c_texture->height = mlx_texture->height;
	if (convert_mlx_texture_to_color(mlx_texture, c_texture))
	{
		mlx_delete_texture(mlx_texture);
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	}
	mlx_delete_texture(mlx_texture);
	return (0);
}

int	convert_mlx_texture_to_color(mlx_texture_t *mlx_texture, t_texture *c_texture)
{
	size_t	i;
	size_t	pixel;

	c_texture->color = malloc(mlx_texture->width * mlx_texture->height * sizeof(t_color));
	if (c_texture->color == NULL)
		return (-1);
	i = 0;
	while (i < mlx_texture->width * mlx_texture->height)
	{
		pixel = i * mlx_texture->bytes_per_pixel;
		// if (i < 1000000)
		// {
		// 	c_texture->color[i].r = 0.5;
		// 	c_texture->color[i].g = 0.5;
		// 	c_texture->color[i].b = 0;
		// }
		// else if (i < 1500000)
		// {
		// 	c_texture->color[i].r = 0.5;
		// 	c_texture->color[i].g = 0;
		// 	c_texture->color[i].b = 0.5;
		// }
		// else
		// {
		// 	c_texture->color[i].r = 0;
		// 	c_texture->color[i].g = 0.5;
		// 	c_texture->color[i].b = 0;
		// }
		c_texture->color[i].r = mlx_texture->pixels[pixel] / 255.0;
		c_texture->color[i].g = mlx_texture->pixels[pixel + 1] / 255.0;
		c_texture->color[i].b = mlx_texture->pixels[pixel + 2] / 255.0;
		i++;
	}
	return (0);
}

t_texture	*parse_c_texture_find(t_list *l_texture, const char *name)
{
	while (l_texture)
	{
		if (ft_strcmp(texture_cont(l_texture)->name, name) == 0)
			return (texture_cont(l_texture));
		l_texture = l_texture->next;
	}
	return (NULL);
}
