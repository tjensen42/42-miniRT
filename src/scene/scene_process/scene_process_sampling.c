#include "miniRT.h"
#include "../scene.h"

int process_sampling(t_scene *scene, char **split, int line_num)
{
	if (scene->sampling.set == true)
		return (scene_print_error(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (split_count(split) != 5)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (str_to_int(split[1], 0, INT_MAX, &(scene->sampling.max_samp)))
		return (scene_print_error(line_num, ERR_PARSE, "Invalid number of max_samp", NULL));
	if (scene->sampling.max_samp == 0)
		scene->sampling.max_samp = INT_MAX;
	if (str_to_int(split[2], 1, INT_MAX, &(scene->sampling.recursion_depth)))
		return (scene_print_error(line_num, ERR_PARSE, "Invalid number of rec_depth", NULL));
	if (str_to_double(split[3], 1, 2, &(scene->sampling.cosine_samp)))
		return (scene_print_error(line_num, ERR_PARSE, "Invalid cosine sampling", NULL));
	if (str_to_double(split[4], 1, 2, &(scene->sampling.import_samp)))
		return (scene_print_error(line_num, ERR_PARSE, "Invalid Import sampling", NULL));
	if (scene->sampling.cosine_samp + scene->sampling.import_samp != 1)
		return (scene_print_error(line_num, ERR_PARSE, "Cosine + Import not equal 1", NULL));
	scene->sampling.set = true;
	return (0);
}
