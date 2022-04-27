#include "mrt_is.h"

t_list	*is_new(void)
{
	t_is	*c_is;

	c_is = malloc(sizeof(t_is));
	if (c_is == NULL)
		return (NULL);
	ft_bzero(c_is, sizeof(t_is));
	return (ft_lstnew(c_is));
}

inline t_is	*is_cont(t_list *is)
{
	return ((t_is *)is->content);
}
