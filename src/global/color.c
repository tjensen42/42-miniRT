#include "miniRT.h"

inline double	color_range(double color, double min, double max)
{
	if (color < min)
		return (min);
	if (color > max)
		return (max);
	return (color);
}

inline t_color	color_add(t_color c1, t_color c2)
{
	return ((t_color){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

inline t_color	color_scale(double f, t_color c1)
{
	return ((t_color){f * c1.r, f * c1.g, f * c1.b});
}

inline t_color	color_multiply(t_color c1, t_color c2)
{
	return ((t_color){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}

inline t_color	color_blend(double f, t_color c1, t_color c2)
{
	return ((t_color){(1.0 - f) * c1.r + f * c2.r, (1.0 - f) * c1.g + f * c2.g, (1.0 - f) * c1.b + f * c2.b});
}

inline t_color	color_gamma_encode(t_color color)
{
	return ((t_color){sqrt(color.r), sqrt(color.g), sqrt(color.b)});
}

inline int	color_to_int(t_color color)
{
	if (color.r != color.r)
		color.r = 0;
	if (color.g != color.g)
		color.g = 0;
	if (color.b != color.b)
		color.b = 0;
	color = color_gamma_encode(color);
	return (
		(int)(256.0 * color_range(color.r, 0.0, 0.999)) << 16 |
		(int)(256.0 * color_range(color.g, 0.0, 0.999)) << 8 |
		(int)(256.0 * color_range(color.b, 0.0, 0.999))
			);
}

void	color_print(t_color color)
{
	printf("\t%-10s %s%8d %s%8d %s%8d%s\n",
		"color:", COLOR_RE, (int)(256 * color_range(color.r, 0.0, 0.999)), COLOR_GR, (int)(256 * color_range(color.g, 0.0, 0.999)), COLOR_BL, (int)(256 * color_range(color.b, 0.0, 0.999)), COLOR_NO);
}

