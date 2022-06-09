/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_trace_onb.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:55:18 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:55:19 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_TRACE_ONB_H
# define MRT_TRACE_ONB_H

# include "mrt_vec3.h"
# include "math/mrt_math.h"

typedef struct s_onb
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
}	t_onb;

t_onb	onb_build(t_vec3 in);
t_vec3	onb_transform(t_onb onb, t_vec3 in);

#endif // MRT_TRACE_ONB_H
