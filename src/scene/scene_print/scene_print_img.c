#include "miniRT.h"
#include "../scene.h"

void	print_img(struct s_img *img)
{
	printf("IMAGE:\n");
	if (img->ppm)
		printf("\t%-10s %8s\n", "ppm:", "true");
	else
		printf("\t%-10s %8s\n", "ppm:", "false");
	scene_print_int(img->width, "width:", NULL);
	scene_print_int(img->height, "height:", NULL);
	vec3_print(img->pos, "img-pos:", COLOR_BL);
	vec3_print(img->px, "img-x:", COLOR_CY);
	vec3_print(img->py, "img-y:", COLOR_CY);
	printf("\n");
}
