#include "mrt_parse.h"

int	parse_sampling(t_scene *scene, char **split, int line_num)
{
	if (scene->sampling.set == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_DUPLICATE, ID_SAMPLING));
	if (ft_split_count_str(split) != 6)
		return (print_error_scene(line_num, ERR_PARSE, ERR_NUM_PARA, NULL));
	if (int_from_str(split[1], 1, 9999, &(scene->sampling.max_samp)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_MAX_SAMP, NULL));
	if (int_from_str(split[2], 1, 1000, &(scene->sampling.recursion_depth)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_REC_DEPTH, NULL));
	if (double_from_str(split[3], 1, 4, &(scene->sampling.cosine)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_COSINE_SAMP, NULL));
	if (double_from_str(split[4], 1, 4, &(scene->sampling.light)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_IMPORT_SAMP, NULL));
	if (scene->sampling.cosine + scene->sampling.light != 1.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_SAMP_SUM, NULL));
	if (ft_strcmp(split[5], "true") != 0 && ft_strcmp(split[5], "false") != 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_GAMMA, NULL));
	scene->sampling.gamma_correction = (ft_strcmp(split[5], "true") == 0);
	scene->sampling.set = true;
	return (0);
}
