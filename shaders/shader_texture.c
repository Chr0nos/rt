/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 18:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/08/16 00:26:23 by snicolet         ###   ########.fr       */
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
	t_v4d	v0;
	t_v4d	v1;
	t_v4d	v2;
	t_v4d	bary;
	double	invdenom;

	v0 = geo_subv4(((t_triangle*)(obj->content))->v2.pos, ((t_triangle*)(obj->content))->v1.pos);
	v1 = geo_subv4(((t_triangle*)(obj->content))->v3.pos, ((t_triangle*)(obj->content))->v1.pos);
	v2 = geo_subv4(i, ((t_triangle*)(obj->content))->v1.pos);

	invdenom = 1.0 / (geo_dotv4(v0, v0) * geo_dotv4(v1, v1) - geo_dotv4(v0, v1) * geo_dotv4(v0, v1));
	bary = (t_v4d){
	(geo_dotv4(v1, v1) * geo_dotv4(v0, v2) - geo_dotv4(v0, v1) * geo_dotv4(v1, v2)) * invdenom,
	(geo_dotv4(v0, v0) * geo_dotv4(v1, v2) - geo_dotv4(v0, v1) * geo_dotv4(v0, v2)) * invdenom,
	0.0,
	0.0
	};
	bary.z = 1.0 - bary.x - bary.y;
	return ((t_v2f){
		(float)(bary.x * (double)((t_triangle*)(obj->content))->v1.uv.x + bary.y *
		(double)((t_triangle*)(obj->content))->v2.uv.x + bary.z * (double)((t_triangle*)(obj->content))->v3.uv.x),
		(float)(bary.x * (double)((t_triangle*)(obj->content))->v1.uv.y + bary.y *
		(double)((t_triangle*)(obj->content))->v2.uv.y + bary.z * (double)((t_triangle*)(obj->content))->v3.uv.y)
	});
}

unsigned int		shader_color_texture_intersection(const t_render *r)
{
	const t_texture		*tex = rt_obj_get_texture(r->obj_intersect);
	const unsigned int	*pixels_texture = (tex) ? tex->surface->pixels : NULL;
	t_v2f				uv;
	static int			t = 0;

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
		if (!t)
		{
			printf("%f %f\n", (double)uv.x, (double)uv.y);
			t++;
		}
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
