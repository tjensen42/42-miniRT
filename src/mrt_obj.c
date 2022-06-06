#include "mrt_obj.h"
#include "lib/libmlx/include/MLX42/MLX42.h"

t_list	*obj_new(void)
{
	t_obj	*c_obj;

	c_obj = malloc(sizeof(t_obj));
	if (c_obj == NULL)
		return (NULL);
	ft_bzero(c_obj, sizeof(t_obj));
	return (ft_lstnew(c_obj));
}

t_list	*texture_new(void)
{
	t_texture	*c_texture;

	c_texture = malloc(sizeof(t_texture));
	if (c_texture == NULL)
		return (NULL);
	ft_bzero(c_texture, sizeof(t_texture));
	return (ft_lstnew(c_texture));
}

void	c_texture_destroy(void *in)
{
	t_texture	*texture;

	texture = in;
	free(texture->name);
	texture->name = NULL;
	if (texture->color)
		free(texture->color);
	texture->color = NULL;
	free(texture);
}

inline t_material	*obj_material(t_list *obj)
{
	return (&(obj_cont(obj)->material));
}

inline t_texture	*obj_texture(t_list *obj)
{
	return (obj_cont(obj)->material.c_texture);
}

inline t_texture	*texture_cont(t_list *texture)
{
	return ((t_texture *)texture->content);
}

inline int obj_type(t_list *obj)
{
	return (*((int *)obj->content));
}

inline t_obj	*obj_cont(t_list *obj)
{
	return ((t_obj *)obj->content);
}

inline t_color	obj_color(t_list *obj, t_hit *hit __attribute__((unused)))
{
	return (obj_cont(obj)->material.color);
}
