#ifndef MRT_GRAPHIC_H
# define MRT_GRAPHIC_H

# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_obj.h"
# include "mrt_scene.h"
# include "math/mrt_math.h"
# include "trace/mrt_trace.h"
# include "lib/libmlx/include/MLX42/MLX42.h"

# define WIN_NAME		"miniRT"

typedef struct s_graphic_data
{
	mlx_t		*mlx;
	mlx_image_t	*mlx_img;
	t_scene		*scene;
}	t_graphic_data;

int	graphic(t_scene *scene);

#endif // MRT_GRAPHIC_H