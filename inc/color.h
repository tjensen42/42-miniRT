#ifndef COLOR_H
# define COLOR_H

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define	COLOR_NO		"\033[m"
# define	COLOR_RE		"\033[0;31m"
# define	COLOR_YE		"\033[0;33m"
# define	COLOR_GR		"\033[0;32m"
# define	COLOR_BL		"\033[0;34m"
# define	COLOR_PL		"\033[0;35m"
# define	COLOR_CY		"\033[0;36m"

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

double	color_range(double color, double min, double max);
t_color	color_add(t_color c1, t_color c2);
t_color	color_scale(double f, t_color c1);
t_color	color_multiply(t_color c1, t_color c2);
t_color	color_blend(double f, t_color c1, t_color c2);
t_color	color_gamma_encode(t_color color);
int		color_to_int(t_color color);
void	color_print(t_color color);

#endif // COLOR_H
