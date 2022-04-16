#include "miniRT.h"
#include "../scene.h"

int	scene_print(t_scene *scene)
{
	t_list *iter;

	scene_print_info(scene);
	print_img(&(scene->img));
	print_sampling(&scene->sampling);
	print_cam(&(scene->cam));
	print_bg(scene->bg);
	print_amb(&(scene->amb));
	iter = scene->l_obj;
	while (iter)
	{
		object_cont(iter)->print(iter);
		iter = iter->next;
	}
	iter = scene->l_is;
	while (iter)
	{
		iter = iter->next;
	}
	return (0);
}

int	scene_print_error(int line_num, const char *msg1, const char *msg2, const char *msg3)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (line_num > 0)
	{
		write(STDERR_FILENO, "line ", 5);
		ft_putnbr_fd(line_num, STDERR_FILENO);
		write(STDERR_FILENO, ": ", 2);
	}
	if (msg1)
		write(STDERR_FILENO, msg1, ft_strlen(msg1));
	if (msg2)
	{
		if (msg1)
			write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, msg2, ft_strlen(msg2));
	}
	if (msg3)
	{
		if (msg1 || msg2)
			write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, msg3, ft_strlen(msg3));
	}
	write(STDERR_FILENO, "\n", 1);
	return (ERROR);
}
