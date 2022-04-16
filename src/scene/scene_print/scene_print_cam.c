#include "miniRT.h"
#include "../scene.h"

void	print_cam(struct s_cam *cam)
{
	printf("CAMERA:\n");
	vec3_print(cam->pos, "pos:", COLOR_BL);
	vec3_print(cam->dir, "dir:", COLOR_CY);
	scene_print_int(cam->fov, "fov:", NULL);
	printf("\n");
}
