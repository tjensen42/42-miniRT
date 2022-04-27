#include "mrt_parse.h"

int parse_sampling(t_scene *scene, char **split, int line_num)
{
	if (scene->sampling.set == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_PARSE_DUP, NULL));
	if (ft_split_count_str(split) != 5)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	if (int_from_str(split[1], 0, INT_MAX, &(scene->sampling.max_samp)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid number of max_samp", NULL));
	if (scene->sampling.max_samp == 0)
		scene->sampling.max_samp = INT_MAX;
	if (int_from_str(split[2], 1, INT_MAX, &(scene->sampling.recursion_depth)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid number of rec_depth", NULL));
	if (double_from_str(split[3], 1, 2, &(scene->sampling.cosine_samp)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid cosine sampling", NULL));
	if (double_from_str(split[4], 1, 2, &(scene->sampling.import_samp)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid Import sampling", NULL));
	if (scene->sampling.cosine_samp + scene->sampling.import_samp != 1)
		return (print_error_scene(line_num, ERR_PARSE, "Cosine + Import not equal 1", NULL));
	scene->sampling.set = true;
	return (0);
}