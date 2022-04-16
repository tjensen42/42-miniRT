#include "miniRT.h"
#include "../scene.h"

void	print_sampling(struct s_sampling *sampling)
{
	printf("SAMPLING:\n");
	scene_print_int(sampling->max_samp, "samples:", NULL);
	scene_print_int(sampling->recursion_depth, "rec_depth:", NULL);
	scene_print_double(sampling->cosine_samp, "cosine:", NULL);
	scene_print_double(sampling->import_samp, "import:", NULL);
	printf("\n");
}
