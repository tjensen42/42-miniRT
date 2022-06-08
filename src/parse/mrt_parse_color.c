#include "mrt_parse.h"

int	parse_color(const char *str, t_color *color)
{
	char	**split;
	int		primary;

	split = ft_split(str, ',');
	if (split == NULL)
		return (-1);
	if (ft_split_count_str(split) != 3)
	{
		ft_free_split(&split);
		return (-1);
	}
	if (int_from_str(split[0], 0, 255, &primary))
		return (-1);
	(*color).r = (double)primary / 255.0;
	if (int_from_str(split[1], 0, 255, &primary))
		return (-1);
	(*color).g = (double)primary / 255.0;
	if (int_from_str(split[2], 0, 255, &primary))
		return (-1);
	(*color).b = (double)primary / 255.0;
	ft_free_split(&split);
	return (0);
}
