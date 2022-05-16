#include "mrt_parse.h"

static double	get_double(const char *str);

int	int_from_str(const char *str, int min, int max, int *res)
{
	int	i;

	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	*res = ft_atoi(str);
	if (*res < min || *res > max)
		return (-1);
	return (0);
}

int	double_from_str(const char *str, int before_point,
				int after_point, double *res)
{
	int	i;

	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (-1);
		i++;
	}
	*res = get_double(str);
	if (str[0] == '+' || str[0] == '-')
		str = str + 1;
	if (ft_strchr(str, '.') != ft_strrchr(str, '.'))
		return (-1);
	if (ft_strchr(str, '.') && (int)(ft_strchr(str, '.') - str) > before_point)
		return (-1);
	if (ft_strchr(str, '.') && (int)(ft_strlen(ft_strchr(str, '.') + 1)) > after_point)
		return (-1);
	if (ft_strchr(str, '.') && !ft_isdigit(*(ft_strchr(str, '.') + 1)))
		return (-1);
	if (!ft_strchr(str, '.') && (int)(ft_strlen(str)) > before_point)
		return (-1);
	return (0);
}

static double	get_double(const char *str)
{
	double	value;
	double	factor;
	int		i;

	i = 0;
	value = 0.0;
	factor = 1;
	if (str[i] == '-')
		factor = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10.0 + (str[i] - '0');
		factor = factor / 10.0;
		i++;
	}
	return (factor * value);
}
