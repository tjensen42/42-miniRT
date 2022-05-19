#include "mrt_trace.h"

// t_vec3	diffuse(t_list *obj __attribute__((unused)), t_ray *ray __attribute__((unused)), t_hit *hit)
// {
// 	if (hit->side == OUTSIDE)
// 		return (vec3_normalize(vec3_add(hit->normal, vec3_normalize(random_in_unit_sphere()))));
// 	else
// 		return (vec3_normalize(vec3_add(vec3_scale(-1.0, hit->normal), vec3_normalize(random_in_unit_sphere()))));
// }
