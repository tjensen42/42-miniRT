#ifndef ONB_H
# define ONB_H

# include "mrt_vec3.h"
# include "math/mrt_math.h"

typedef struct s_onb
{
	t_vec3 u;
	t_vec3 v;
	t_vec3 w;
}	t_onb;

t_onb	onb_build(t_vec3 in);
t_vec3	onb_transform(t_onb onb, t_vec3 in);

#endif // ONB_H
