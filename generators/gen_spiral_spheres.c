#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define SIZE_X			750
#define SIZE_Y			750

#define SPHERES			1800

#define SPHERE_RADIUS	2.0

#define SPRIAL_DISTANCE	0.05
#define SPHERE_DISTANCE	15000

#define SCATTERING		1.0
#define REFLECTION		0.0
#define REFLECTION_FUZZ	0.0
#define TRANSMISSION	0.0
#define SCATTER_REFLEC	0.0

#define DEG2RAD			(M_PI/180.0)

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

double random_double(double min, double max)
{
    double div = RAND_MAX / (max - min);
    return (min + (rand() / div));
}

double	vec3_len(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
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
	if (random < 0.2)
		return ((t_color){255, 255, 255});
	else if (random < 0.4)
		return ((t_color){188, 84, 185});
	else if (random < 0.6)
		return ((t_color){234, 203, 86});
	else if (random < 0.8)
		return ((t_color){25, 25, 25});
	else
		return ((t_color){89, 183, 186});
	return (color);
}

t_color	gen_color_i(int j)
{
	int		rainbow_count;
	t_color color;

	rainbow_count = 120;
	int i = j % rainbow_count;
	if (i < (rainbow_count) / 6)
	{
		color.r = 255;
		color.g = i / ((double)(rainbow_count) / 6.0) * 255;
		color.b = 0;
	}
	else if (i < (rainbow_count) / 6 * 2)
	{
		color.r = 255 - (i - (rainbow_count) / 6) / ((double)(rainbow_count) / 6.0) * 255;
		color.g = 255;
		color.b = 0;
	}
	else if (i < (rainbow_count) / 6 * 3)
	{
		color.r = 0;
		color.g = 255;
		color.b = (i - (rainbow_count) / 6 * 2) / ((double)(rainbow_count) / 6.0) * 255;
	}
	else if (i < (rainbow_count) / 6 * 4)
	{
		color.r = 0;
		color.g = 255 - (i - (rainbow_count) / 6 * 3) / ((double)(rainbow_count) / 6.0) * 255;
		color.b = 255;
	}
	else if (i < (rainbow_count) / 6 * 5)
	{
		color.r = (i - (rainbow_count) / 6 * 4) / ((double)(rainbow_count) / 6.0) * 255;
		color.g = 0;
		color.b = 255;
	}
	else
	{
		color.r = 255;
		color.g = 0;
		color.b = 255 - (i - (rainbow_count) / 6 * 5) / ((double)(rainbow_count) / 6.0) * 255;
	}
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

t_sphere gen_sphere_on_archimedisch_spiral(int i)
{
	double		theta;
	t_sphere	sphere;

	theta = sqrt((double)i / (double)(SPHERES - 1) * (SPHERES - 1) * SPHERE_DISTANCE);
	sphere.radius = SPHERE_RADIUS;
	// sphere.radius = random_double(0.5, 2.5);
	sphere.pos = (t_vec3){SPRIAL_DISTANCE * theta * cos(theta * DEG2RAD), sphere.radius + 0.2 * i, SPRIAL_DISTANCE * theta * sin(theta * DEG2RAD)};
	sphere.color = gen_color_i(i);
	sphere.surface = gen_surface();
	return (sphere);
}

int	main(int argc, char *argv[])
{
	printf("## RESOLUTION #########################################################################################################\n# | width  | height | #################################################################################################\n#######################################################################################################################\n");
	printf("R   %d     %d\n\n", SIZE_X, SIZE_Y);

	printf("## SAMPLING ###########################################################################################################\n# | samples  | bounces | cos sampling   | light sampling | gamma (color correction) ###################################\n#######################################################################################################################\n");
	printf("S   5000       30        1.0             0.0             true\n\n");

	printf("## BACKGROUND #########################################################################################################\n# | top color    | bottom color | #####################################################################################\n#######################################################################################################################\n");
	// printf("B   255,255,255    255,255,255\n\n");
	printf("B   128,179,255    255,255,255\n\n");

	printf("## CAMERA #############################################################################################################\n# | look from         | look at           | fov | #####################################################################\n#######################################################################################################################\n");
	printf("C   +0.00,+060.00,+220.00   +20.00,+100.00,+30.00   60\n\n");

	printf("## AMBIENT LIGHT ######################################################################################################\n# | ratio | color       | #############################################################################################\n#######################################################################################################################\n");
	printf("A   0.0     255,255,255\n\n");

	// printf("## LIGHT (SPHERE) #####################################################################################################\n# | position          | radius | color       | brightness | sampling factor | #########################################\n#######################################################################################################################\n");
	// printf("ls  +0.00,+100.0,+0.00   10      255,255,255   500.0        1\n\n");

	printf("## SPHERE #############################################################################################################\n# | position          | radius | color       | material                  | ############################################\n#######################################################################################################################\n");
	printf("sp  +0.00,+40.00,+0.00   40   250,250,250   0.0,0.0,1.0,0.0  0.0  1.5\n\n");
	printf("sp  +160.00,+60.00,-200.00   60   210,210,210   0.0,1.0,0.0,0.0  0.0  1.5\n\n");

	printf("## PLANE ##############################################################################################################\n# | position          | direction         | color       | material                  | #################################\n#######################################################################################################################\n");
	printf("pl  +0.00,+0.00,+0.00   +0.00,+1.00,+0.00   010,010,010   0.8,0.2,0.0,0.0  0.0  1.5\n\n");

	printf("## SPHERE #############################################################################################################\n# | position          | radius | color       | material                  | ############################################\n#######################################################################################################################\n");


	int			i;
	t_sphere	spheres[SPHERES];

	srand(time(NULL));
	memset(spheres, 0, SPHERES * sizeof(t_sphere));

	i = 0;
	while (i < SPHERES)
	{
		spheres[i] = gen_sphere_on_archimedisch_spiral(i);
		i++;
	}

	i = 0;
	while (i < SPHERES)
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


