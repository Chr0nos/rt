/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hantlowt <hantlowt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 16:13:19 by hantlowt          #+#    #+#             */
/*   Updated: 2016/08/25 22:45:16 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rt.h"
#include "shaders.h"

void			shader_shadow(t_shader *s, t_render *r, t_obj *light)
{
	t_ray			ray;
	t_render		sw;
	unsigned int	shadow;
	unsigned int	color;

	ray = *r->ray;
	ray.start = geo_addv4(r->intersection, geo_multv4(ray.dir,
		geo_dtov4d(-0.00001)));
	ray.dir = (light->type == SUNLIGHT ? geo_normv4(light->trans.w) :
		geo_normv4(geo_subv4(light->trans.w, r->intersection)));
	//ray.lenght = (double)INFINITY;
	sw = (t_render){&ray, r->rt, NULL, HUGE_VAL, 0.0,
			(t_v4d){0.0, 0.0, 0.0, 0.0}, ray.dir};
	rt_node_foreach(sw.rt->tree.bounded, INFIX, &rt_render_foreach, &sw);
	rt_node_foreach(sw.rt->tree.unbounded, INFIX, &rt_render_foreach, &sw);
	color = 0x0;
	shadow = (light->type == SUNLIGHT ? 0x55000000 : 0x11000000);
	if (sw.obj_intersect)
	{
		if (rt_obj_get_texture(sw.obj_intersect))
			color = shader_color_texture_intersection(&sw);
		else
			color = ((t_cube*)(sw.obj_intersect->content))->color;
		if (sw.obj_intersect != r->obj_intersect &&
			((geo_distv4(light->trans.w, r->intersection)
		> geo_distv4(sw.obj_intersect->trans.w, r->intersection))
		|| (light->type == SUNLIGHT)))
		{
			if (A(color))
			{
				//shadow = to_rgb(0x11, 0, 0, 0);
				color = to_rgb(0xFF, R(color), G(color), B(color));
				//color = blend_sub(0xFFFFFF, color);
				s->color_render = blend_add(color, s->color_render);
			}
			s->color_render = blend_sub(s->color_render, shadow);
			//s->color_render= to_rgb(0xFF, R(s->color_render), G(s->color_render), B(s->color_render));
			//shaders_disable_nexts(s);
		}
	}
	//else
	//	s->color_render = blend_add(s->color_render, shadow);
}
