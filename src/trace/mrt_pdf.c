#include "mrt_trace.h"

double mixed_sampling_pdf(t_hit *hit, t_hit *hit2, t_vec3 dir, double light_cosine)
{
	double cosine_pdf;
	double light_area = 1 * 1 * M_PI;

	double cosine = vec3_scalar_product(hit->normal, dir);
	if (cosine <= 0)
		cosine_pdf = 0;
	else
		cosine_pdf = cosine / M_PI;
	// double light_pdf = distance_squared / (light_cosine * light_area);
	double light_pdf = (hit2->t * hit2->t) / (light_cosine * light_area);

	// while (lights)
	// {
	// 	light_pdf += (hit2->t * hit2->t) / (light_cosine * light_area);
	// 	light_pdf += obj_pdf[obj_type(obj)](l_scene, ray, obj, hit);
	// }
	// light_pdf /= lights.count;

	// fprintf(stderr, "light_pdf: %f\n", light_pdf);
	return (1 * cosine_pdf + 0 * light_pdf);
}
