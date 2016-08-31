/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hantlowt <hantlowt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 16:13:19 by hantlowt          #+#    #+#             */
/*   Updated: 2016/08/31 14:46:08 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rt.h"
#include "shaders.h"

static void		set_color_shader_shadow(t_render *r, unsigned int *render,
	t_render *sw, t_obj *light)
{
	unsigned int	shad;
	unsigned int	color;

	shad = (light->type == SUNLIGHT ? 0x55000000 : 0x99000000);
	color = 0x0;
	if (sw->obj_intersect)
	{
		color = shader_color_texture_intersection(sw);
		if (sw->obj_intersect != r->obj_intersect &&
			((geo_distv4(light->trans.w, r->intersection)
		> geo_distv4(sw->obj_intersect->trans.w, r->intersection))
		|| (light->type == SUNLIGHT)))
		{
			if (A(color))
			{
				shad = blend_add(shad, to_rgb(A(color) / 2, 0, 0, 0));
				color = blend_multiply(to_rgb(0, R(color), G(color), B(color)),
				to_rgb(0, A(color), A(color), A(color)));
				*render = blend_add(color, *render);
			}
			*render = blend_sub(*render, shad);
		}
	}
}

void			shader_shadow(t_shader *s, t_render *r, t_obj *light, unsigned int *color_render)
{
	t_ray			ray;
	t_render		sw;

	(void)s;
	ray = *r->ray;
	ray.start = geo_addv4(r->intersection, geo_multv4(ray.dir,
		geo_dtov4d(-0.00001)));
	ray.dir = (light->type == SUNLIGHT ? geo_normv4(light->trans.w) :
		geo_normv4(geo_subv4(light->trans.w, r->intersection)));
	sw = (t_render){&ray, r->rt, NULL, HUGE_VAL, 0.0,
			(t_v4d){0.0, 0.0, 0.0, 0.0}, ray.dir, color_render};
	rt_node_foreach(sw.rt->tree.bounded, INFIX, &rt_render_foreach, &sw);
	rt_node_foreach(sw.rt->tree.unbounded, INFIX, &rt_render_foreach, &sw);
	set_color_shader_shadow(r, color_render, &sw, light);
}
