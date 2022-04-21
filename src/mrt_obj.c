#include "mrt_obj.h"

t_list	*obj_new(int type)
{
	t_obj	*c_obj;

	c_obj = malloc(sizeof(t_obj));
	if (c_obj == NULL)
		return (NULL);
	ft_bzero(c_obj, sizeof(t_obj));
	c_obj->type = type;
	return (ft_lstnew(c_obj));
}

inline int obj_type(t_list *obj)
{
	return (*((int *)obj->content));
}

inline t_obj	*obj_cont(t_list *obj)
{
	return ((t_obj *)obj->content);
}
