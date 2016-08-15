/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 18:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/08/15 11:36:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "shaders.h"
#include "texture.h"
#include "libft.h"
#include "mesh.h"

static t_v2f		get_uv_triangle(t_obj *obj, t_v4d i)
{
	t_vertex	va;
	t_vertex	vb;
	t_vertex	vc;
	t_v4d	bary;

	va = ((t_triangle*)(obj->content))->v1;
	vb = ((t_triangle*)(obj->content))->v2;
	vc = ((t_triangle*)(obj->content))->v1;

	bary = (t_v4d){
	((vb.pos.y - vc.pos.y)*(i.x - vc.pos.x) + (vc.pos.x - vb.pos.x)*(i.y - vc.pos.y)) /
	((vb.pos.y - vc.pos.y)*(va.pos.x - vc.pos.x) + (vc.pos.x - vb.pos.x)*(va.pos.y - vc.pos.y)),
	((vc.pos.y - va.pos.y)*(i.x - vc.pos.x) + (va.pos.x - vc.pos.x)*(i.y - vc.pos.y)) /
	((vb.pos.y - vc.pos.y)*(va.pos.x - vc.pos.x) + (vc.pos.x - vb.pos.x)*(va.pos.y - vc.pos.y)),
	1 - bary.x - bary.y,
	0.0
	};
	return ((t_v2f){
		(float)(bary.x * (double)va.uv.x + bary.y * (double)vb.uv.x + bary.z * (double)vc.uv.x),
		(float)(bary.x * (double)va.uv.y + bary.y * (double)vb.uv.y + bary.z * (double)vc.uv.y)
	});
}

unsigned int		shader_color_texture_intersection(const t_render *r)
{
	const t_texture		*tex = rt_obj_get_texture(r->obj_intersect);
	const unsigned int	*pixels_texture = (tex) ? tex->surface->pixels : NULL;
	t_v2f				uv;

	if (!pixels_texture)
		return (0);
	if (r->obj_intersect->type & SPHERE)
	{
		uv = (t_v2f){
			(float)(0.5 + (atan2(r->normal.z, r->normal.x) / (2.0 * M_PI))),
			(float)(0.5 - (asin(r->normal.y) / M_PI))
		};
	}
	else if (r->obj_intersect->type & TRIANGLE)
	{
		uv = get_uv_triangle(r->obj_intersect, r->intersection);
	}
	else
	{
		uv = (t_v2f){
			(float)fabs((double)((int)(((r->normal.x != 0.0 ? r->intersection.z :
			r->intersection.x) * 1.0) * 1000.0) % 1000) * 0.001),
			(float)fabs((double)((int)(((r->normal.y != 0.0 ? r->intersection.z :
			r->intersection.y) * 1.0) * 1000.0) % 1000) * 0.001)
		};
	}
	return (draw_suv(tex->surface, uv));
}

void				shader_texture(t_shader *s, t_render *r, t_obj *light)
{
	(void)light;
	(void)s;
	if (rt_obj_get_texture(r->obj_intersect))
		s->color_render = shader_color_texture_intersection(r);
	else
		s->color_render = ((t_cube*)(r->obj_intersect->content))->color;
}
