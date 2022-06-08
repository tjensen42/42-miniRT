#include "lib/libft/inc/libft.h"
#include "mrt_color.h"
#include "mrt_vec3.h"
#include "mrt_obj.h"
#include "math/mrt_math.h"
#include "trace/mrt_trace.h"

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

inline t_texture	*texture_cont(t_list *texture)
{
	return ((t_texture *)texture->content);
}
