#include "mrt_print.h"

void	print_textures(t_list *l_texture)
{
	t_texture	*c_texture;

	printf("TEXTURES:\n");
	while (l_texture)
	{
		c_texture = l_texture->content;
		printf("\t%s: width: %d height: %d\n", c_texture->name, c_texture->width, c_texture->height);
		l_texture = l_texture->next;
	}
	printf("\n");
}
