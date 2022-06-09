/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_print_material.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:57:29 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:57:29 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_print.h"

void	print_material(t_material *material)
{
	print_color(material->color);
	print_scene_double(material->surface[DIFFUSE], "DIFFUSE:", COLOR_PL);
	print_scene_double(material->surface[SPECULAR], "SPECULAR:", COLOR_PL);
	print_scene_double(material->surface[DIELECTRIC], "DIELEC:", COLOR_PL);
	print_scene_double(material->fuzz, "FUZZ:", NULL);
	print_scene_double(material->refraction_index, "REFRAC:", NULL);
	if (material->cb_factor > 0)
		print_scene_int(material->cb_factor, "CB:", COLOR_NO);
	if (material->c_texture)
		printf("\tTEXTURE: %s\n", material->c_texture->name);
}
