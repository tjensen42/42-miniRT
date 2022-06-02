#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define SIZE_X				1500
#define SIZE_Y				1500

#define TOP					0
#define BOTTOM				1

#define FIELD_X_MIN			-2
#define FIELD_X_MAX			9
#define FIELD_Z_MIN			5
#define FIELD_Z_MAX			6

#define THICKNESS			2

#define SPHERES_SUM			2000
#define SPHERES_SQUARE  	(SPHERES_SUM / 10)
#define SPHERES_TRIANGLE	(SPHERES_SUM / 20)
#define SPHERE_MIN_RAD		0.1
#define SPHERE_MAX_RAD		0.5

#define SCATTERING			0.3
#define REFLECTION			0.3
#define REFLECTION_FUZZ		0.2
#define TRANSMISSION		0.2
#define SCATTER_REFLEC		0.0

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_surface
{
	double	scattering;
	double	reflection;
	double	transmission;
	double	fuzz;
}	t_surface;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/* generate a random floating point number from min to max */
double random_double(double min, double max)
{
    double div = RAND_MAX / (max - min);
    return (min + (rand() / div));
}

double	vec3_length(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	vec3_subtract(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

typedef	struct s_sphere
{
	t_vec3		pos;
	double		radius;
	t_color		color;
	t_surface	surface;
}	t_sphere;

t_vec3	random_pos_in_rectangle(double x_min, double x_max, double y_min, double y_max, double z_min, double z_max)
{
	t_vec3	vec3;

	vec3.x = random_double(x_min, x_max);
	vec3.y = random_double(y_min, y_max);
	vec3.z = random_double(z_min, z_max);
	return (vec3);
}

t_vec3	random_pos_in_triangle(double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, int side)
{
	t_vec3	vec3;

	while (1)
	{
		vec3.x = random_double(x_min, x_max);
		// vec3.y = random_double(SPHERE_MIN_RAD, SPHERE_MAX_RAD);
		vec3.y = random_double(y_min, y_max);
		vec3.z = random_double(z_min, z_max);
		if (side == TOP && vec3.x - x_min <= (z_max - z_min) - (vec3.z - z_min) )
			return (vec3);
		else if (side == BOTTOM && vec3.x - x_min >= (z_max - z_min) - (vec3.z - z_min))
			return (vec3);
	}
	return (vec3);
}

int		sphere_overlap(t_sphere sp_a, t_sphere sp_b)
{
	double distance;

	distance = vec3_length(vec3_subtract(sp_a.pos, sp_b.pos));
	if (distance > sp_a.radius + sp_b.radius)
		return (false);
	return (true);
}

// 42 COLOR
// rgb(89, 183, 186) - blau
// rgb(188, 84, 185) - lila
// rgb(234, 203, 86) - gelb
t_color	gen_color_42(t_sphere sphere)
{
	t_color color;
	double	random;

	random = rand() / (double)RAND_MAX;
	if (random < 0.15)
		return ((t_color){255, 255, 255}); // weiß
	else if (random < 0.4)
		return ((t_color){188, 84, 185}); // lila
	else if (random < 0.7)
		return ((t_color){234, 203, 86}); // gelb
	else if (random < 0.85)
		return ((t_color){25, 25, 25}); // black
	else
		return ((t_color){89, 183, 186}); // blau
	return (color);
}

t_color	gen_color(t_sphere sphere)
{
	t_color color;
	double	random;

	random = rand() / (double)RAND_MAX;
	if (random < 0.7)
	{
		color.r = rand() % 256;
		color.g = rand() % 256;
		color.b = rand() % 256;
	}
	else if (random < 0.8)
	{
		color.r = rand() % 256;
		color.g = rand() % 64;
		color.b = rand() % 64;
	}
	else if (random < 0.9)
	{
		color.r = rand() % 64;
		color.g = rand() % 256;
		color.b = rand() % 64;
	}
	else
	{
		color.r = rand() % 64;
		color.g = rand() % 64;
		color.b = rand() % 256;
	}
	return (color);
}

t_surface	gen_surface()
{
	double		random_choose;
	t_surface	surf;

	random_choose = random_double(0.0, 1.0);
	if (random_choose < SCATTERING)
		return ((t_surface){1.0, 0.0, 0.0, 0.0});
	else if (random_choose < SCATTERING + REFLECTION)
		return ((t_surface){0.0, 1.0, 0.0, 0.0});
	else if (random_choose < SCATTERING + REFLECTION + REFLECTION_FUZZ)
		return ((t_surface){0.0, 1.0, 0.0, random_double(0.0, 0.6)});
	else if (random_choose < SCATTERING + REFLECTION + REFLECTION_FUZZ + TRANSMISSION)
		return ((t_surface){0.0, 0.0, 1.0, 0});
	else
		return ((t_surface){0.8, 0.2, 0.0, 0});
}

t_sphere gen_sphere_in_rectangle(t_sphere *spheres, int sphere_count, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max)
{
	int 		i;
	t_sphere	tmp;

	tmp.pos = random_pos_in_rectangle(x_min, x_max, y_min, y_max, z_min, z_max);
	tmp.radius = random_double(SPHERE_MIN_RAD, SPHERE_MAX_RAD);
	i = 0;
	while (i < sphere_count)
	{
		if (sphere_overlap(spheres[i], tmp))
		{
			tmp.pos = random_pos_in_rectangle(x_min, x_max, y_min, y_max, z_min, z_max);
			tmp.radius = random_double(SPHERE_MIN_RAD, SPHERE_MAX_RAD);
			i = -1;
		}
		i++;
	}
	// tmp.color = gen_color(tmp);
	tmp.color = gen_color_42(tmp);
	tmp.surface = gen_surface();
	return (tmp);
}

t_sphere gen_sphere_in_triangle(t_sphere *spheres, int sphere_count, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, int side)
{
	int 		i;
	t_sphere	tmp;

	tmp.pos = random_pos_in_triangle(x_min, x_max, y_min, y_max, z_min, z_max, side);
	tmp.radius = random_double(SPHERE_MIN_RAD, SPHERE_MAX_RAD);
	i = 0;
	while (i < sphere_count)
	{
		if (sphere_overlap(spheres[i], tmp))
		{
			tmp.pos = random_pos_in_triangle(x_min, x_max, y_min, y_max, z_min, z_max, side);
			tmp.radius = random_double(SPHERE_MIN_RAD, SPHERE_MAX_RAD);
			i = 0;
			continue ;
		}
		i++;
	}
	// tmp.color = gen_color(tmp);
	tmp.color = gen_color_42(tmp);
	tmp.surface = gen_surface();
	return (tmp);
}

int	main(int argc, char *argv[])
{
	int			i;
	int			j;
	t_sphere	spheres[SPHERES_SUM];

	printf("## RESOLUTION #########################################################################################################\n# | width  | height | #################################################################################################\n#######################################################################################################################\n");
	printf("R   %d     %d\n\n", SIZE_X, SIZE_Y);

	printf("## SAMPLING ###########################################################################################################\n# | samples  | bounces | cos sampling   | light sampling | gamma (color correction) ###################################\n#######################################################################################################################\n");
	printf("S   5000       30        1.00             0.00             false\n\n");

	printf("## BACKGROUND #########################################################################################################\n# | top color    | bottom color | #####################################################################################\n#######################################################################################################################\n");
	printf("B   255,255,255    255,255,255\n\n");

	printf("## CAMERA #############################################################################################################\n# | look from         | look at           | fov | #####################################################################\n#######################################################################################################################\n");
	printf("C   +15.50,+30.00,+25.00   +13.50,+0.00,-10.50   45\n\n");

	printf("## AMBIENT LIGHT ######################################################################################################\n# | ratio | color       | #############################################################################################\n#######################################################################################################################\n");
	printf("A   0.0     255,255,255\n\n");

	printf("## PLANE ##############################################################################################################\n# | position          | direction         | color       | material                  | #################################\n#######################################################################################################################\n");
	printf("pl  +0.00,+0.00,+0.00   +0.00,+1.00,+0.00   089,183,186   1.0,0.0,0.0,0.0  0.1  1.5\n\n");

	printf("## SPHERE #############################################################################################################\n# | position          | radius | color       | material                  | ############################################\n#######################################################################################################################\n");

	srand(time(NULL));
	memset(spheres, 0, SPHERES_SUM * sizeof(t_sphere));

	i = 0;

	// #define SPHERES_SQUARE		(SPHERES_SUM / 6)
	// #define SPHERES_TRIANGLE	(SPHERES_SUM / 12)

	j = 0;
	while (j < SPHERES_SQUARE)
	{
		spheres[i] = gen_sphere_in_rectangle(spheres, i, 10, 15, 0, THICKNESS, -5, 0);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_SQUARE)
	{
		spheres[i] = gen_sphere_in_rectangle(spheres, i, 0, 5, 0, THICKNESS, -10, -5);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_SQUARE)
	{
		spheres[i] = gen_sphere_in_rectangle(spheres, i, 5, 10, 0, THICKNESS, -10, -5);
		i++;
		j++;
	}
	j = 0;
	while (j < SPHERES_SQUARE)
	{
		spheres[i] = gen_sphere_in_rectangle(spheres, i, 10, 15, 0, THICKNESS, -10, -5);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_TRIANGLE)
	{
		spheres[i] = gen_sphere_in_triangle(spheres, i, 0, 5, 0, THICKNESS, -15, -10, BOTTOM);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_TRIANGLE)
	{
		spheres[i] = gen_sphere_in_triangle(spheres, i, 5, 10, 0, THICKNESS, -15, -10, TOP);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_TRIANGLE)
	{
		spheres[i] = gen_sphere_in_triangle(spheres, i, 5, 10, 0, THICKNESS, -20, -15, BOTTOM);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_TRIANGLE)
	{
		spheres[i] = gen_sphere_in_triangle(spheres, i, 10, 15, 0, THICKNESS, -20, -15, TOP);
		i++;
		j++;
	}


	//
	// 2
	//

	j = 0;
	while (j < SPHERES_SQUARE)
	{
		spheres[i] = gen_sphere_in_rectangle(spheres, i, 17, 22, 0, THICKNESS, -10, -5);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_TRIANGLE)
	{
		spheres[i] = gen_sphere_in_triangle(spheres, i, 22, 27, 0, THICKNESS, -10, -5, BOTTOM);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_TRIANGLE)
	{
		spheres[i] = gen_sphere_in_triangle(spheres, i, 17, 22, 0, THICKNESS, -15, -10, BOTTOM);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_TRIANGLE)
	{
		spheres[i] = gen_sphere_in_triangle(spheres, i, 22, 27, 0, THICKNESS, -15, -10, TOP);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_TRIANGLE)
	{
		spheres[i] = gen_sphere_in_triangle(spheres, i, 17, 22, 0, THICKNESS, -20, -15, TOP);
		i++;
		j++;
	}

	j = 0;
	while (j < SPHERES_SQUARE)
	{
		spheres[i] = gen_sphere_in_rectangle(spheres, i, 22, 27, 0, THICKNESS, -20, -15);
		i++;
		j++;
	}

	i = 0;
	while (i < SPHERES_SUM)
	{
		printf("sp  ");
		printf("%+05.2f,%+05.2f,%+05.2f   ", spheres[i].pos.x, spheres[i].pos.y, spheres[i].pos.z);
		printf("%.4f   ", spheres[i].radius);
		printf("%03d,%03d,%03d   ", spheres[i].color.r, spheres[i].color.g, spheres[i].color.b);
		printf("%1.1f,%1.1f,%1.1f,%1.1f  ", spheres[i].surface.scattering, spheres[i].surface.reflection, spheres[i].surface.transmission, 0.0);
		printf("%1.1f  %1.1f\n", spheres[i].surface.fuzz, 1.5);
		i++;
	}
}


