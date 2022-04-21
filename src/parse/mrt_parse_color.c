#include "mrt_parse.h"

int	parse_color(const char *str, t_color *color)
{
	char	**split;
	int		primary;
	int		i;

	if (ft_str_count_chr(str, ',') != 2)
		return (-1);
	split = ft_split(str, ',');
	if (split == NULL)
		return (-1);
	i = 0;
	while (i < 3)
	{
		if (int_from_str(split[i], 0, 255, &primary))
			return (-1);
		if (i == 0)
			(*color).r = (double)primary / 255.0;
		else if (i == 1)
			(*color).g = (double)primary / 255.0;
		else if (i == 2)
			(*color).b = (double)primary / 255.0;
		i++;
	}
	ft_free_split(&split);
	return (0);
}
