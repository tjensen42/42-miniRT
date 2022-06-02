#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define WIN_SIZE_X			1000
#define WIN_SIZE_Y			1000

#define GRID_SPHERES_A		30
#define GRID_SPHERES_B		30
#define GRID_SPHERES_SUM	(GRID_SPHERES_A * GRID_SPHERES_B)

#define SPHERES_RADIUS		1.5
#define SPHERES_PADDING		0.5

#define SCATTERING			1.0
#define REFLECTION			0.0
#define REFLECTION_FUZZ		0.0
#define TRANSMISSION		0.0
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

// 42 COLOR
// rgb(89, 183, 186) - blau
// rgb(188, 84, 185) - lila
// rgb(234, 203, 86) - gelb
t_color	gen_color_42()
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

t_color	gen_color()
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

t_sphere	gen_sphere(int a, int b)
{
	t_sphere	sphere;

	sphere.radius = SPHERES_RADIUS;
	sphere.pos = (t_vec3){a * (SPHERES_RADIUS * 2.0 + SPHERES_PADDING) + SPHERES_RADIUS, sphere.radius, b * (SPHERES_RADIUS * 2.0 + SPHERES_PADDING) + SPHERES_RADIUS};
	sphere.color = gen_color_42();
	sphere.surface = gen_surface();
	return (sphere);
}

int	main(int argc, char *argv[])
{
	printf("## RESOLUTION #########################################################################################################\n# | width  | height | #################################################################################################\n#######################################################################################################################\n");
	printf("R   %d     %d\n\n", WIN_SIZE_X, WIN_SIZE_Y);

	printf("## SAMPLING ###########################################################################################################\n# | samples  | bounces | cos sampling   | light sampling | gamma (color correction) ###################################\n#######################################################################################################################\n");
	printf("S   5000       30        1.00             0.00             false\n\n");

	printf("## BACKGROUND #########################################################################################################\n# | top color    | bottom color | #####################################################################################\n#######################################################################################################################\n");
	printf("B   255,255,255    255,255,255\n\n");

	printf("## CAMERA #############################################################################################################\n# | look from         | look at           | fov | #####################################################################\n#######################################################################################################################\n");
	printf("C   +10.00,+100.00,+100.00   %+06.2f,%+06.2f,%+06.2f  45\n\n", (GRID_SPHERES_A / 2.0) * ((SPHERES_RADIUS * 2.0) + SPHERES_PADDING), 0.0, (GRID_SPHERES_B / 2.0) * ((SPHERES_RADIUS * 2.0) + SPHERES_PADDING));

	printf("## AMBIENT LIGHT ######################################################################################################\n# | ratio | color       | #############################################################################################\n#######################################################################################################################\n");
	printf("A   0.0     255,255,255\n\n");

	printf("## PLANE ##############################################################################################################\n# | position          | direction         | color       | material                  | #################################\n#######################################################################################################################\n");
	printf("pl  +0.00,+0.00,+0.00   +0.00,+1.00,+0.00   089,183,186   1.0,0.0,0.0,0.0  0.1  1.5\n\n");

	printf("## CUBOID #############################################################################################################\n# | position          | width  | height | depth  | rotations         | color       | material                  | ######\n#######################################################################################################################\n");

	int				i, j, k, a, b;
	static t_sphere	spheres[GRID_SPHERES_SUM];

	srand(time(NULL));
	memset(spheres, 0, GRID_SPHERES_SUM * sizeof(t_sphere));

	b = 0;
	while (b < GRID_SPHERES_B)
	{
		a = 0;
		while (a < GRID_SPHERES_A)
		{
			spheres[b * GRID_SPHERES_A + a] = gen_sphere(a, b);
			a++;
		}
		b++;
	}

	i = 0;
	while (i < GRID_SPHERES_SUM)
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
