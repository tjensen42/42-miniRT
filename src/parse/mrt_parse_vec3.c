#include "mrt_parse.h"

int	parse_vec3(const char *str, t_vec3 *vec3)
{
	char	**split;

	if (ft_str_count_chr(str, ',') != 2)
		return (-1);
	split = ft_split(str, ',');
	if (split == NULL)
		return (-1);
	if (double_from_str(split[0], 6, 4, &((*vec3).x)))
		return (-1);
	if (double_from_str(split[1], 6, 4, &((*vec3).y)))
		return (-1);
	if (double_from_str(split[2], 6, 4, &((*vec3).z)))
		return (-1);
	ft_free_split(&split);
	return (0);
}
