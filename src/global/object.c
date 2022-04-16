#include "miniRT.h"

t_list	*object_new(int type)
{
	t_obj	*obj_cont;

	obj_cont = malloc(sizeof(t_obj));
	if (obj_cont == NULL)
		return (NULL);
	ft_memset(obj_cont, 0, sizeof(t_obj));
	obj_cont->type = type;
	return (ft_lstnew(obj_cont));
}

inline int object_type(t_list *obj)
{
	return (*((int *)obj->content));
}

inline t_obj	*object_cont(t_list *obj)
{
	return ((t_obj *)obj->content);
}
