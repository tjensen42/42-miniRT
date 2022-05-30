#include "mrt_light.h"

t_list	*light_new(void)
{
	t_light	*c_light;

	c_light = malloc(sizeof(t_light));
	if (c_light == NULL)
		return (NULL);
	ft_bzero(c_light, sizeof(t_light));
	return (ft_lstnew(c_light));
}

inline t_light	*light_cont(t_list *is)
{
	return ((t_light *)is->content);
}
