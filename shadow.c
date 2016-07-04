/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hantlowt <hantlowt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 16:13:19 by hantlowt          #+#    #+#             */
/*   Updated: 2016/07/04 17:37:09 by hantlowt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rt.h"
#include "shaders.h"

void			shader_shadow(t_shader *s, t_render *r, t_obj *light)
{
	t_ray		ray;
	t_render	shadow;

	ray.start = r->intersection;
	ray.dir = geo_subv4(light->trans.w, r->intersection);
	shadow = (t_render){
			&ray, r->rt,
			NULL,
			HUGE_VAL,
			0.0,
			(t_v4d){0.0, 0.0, 0.0, 0.0},
			ray.dir,
			0.0, 0.0
		};
	rt_render(shadow.rt, &ray);
	if (shadow.obj_intersect)
		s->color_render = blend_lighten(s->color_render, 0);
}
