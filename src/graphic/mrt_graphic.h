/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_graphic.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:50:23 by tjensen           #+#    #+#             */
/*   Updated: 2022/12/19 12:43:34 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_GRAPHIC_H
# define MRT_GRAPHIC_H

# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_obj.h"
# include "mrt_scene.h"
# include "math/mrt_math.h"
# include "trace/mrt_trace.h"
# include "libmlx/include/MLX42/MLX42.h"

# define WIN_NAME		"miniRT"

typedef struct s_graphic_data
{
	mlx_t		*mlx;
	mlx_image_t	*mlx_img;
	t_scene		*scene;
}	t_graphic_data;

int		graphic(t_scene *scene);

void	move(t_scene *scene, t_vec3 new_pos);
void	rotate_horizontal(t_scene *scene, double rot);
void	rotate_vertical(t_scene *scene, bool up, double rot);

void	graphic_render(t_graphic_data *graphic);
void	*draw_thread(void *thread_data);
void	img_to_mlx_img(t_scene *scene, mlx_image_t *mlx_img);

void	reset_cam(t_scene *scene);
void	reset_sampling(t_scene *scene);

#endif // MRT_GRAPHIC_H
