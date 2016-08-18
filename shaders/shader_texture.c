/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 18:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/08/18 21:17:49 by alhote           ###   ########.fr       */
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
	t_v4d	f1;
	t_v4d	f2;
	t_v4d	f3;
	t_v4d	bary;

	f1 = geo_subv4(((t_triangle*)(obj->content))->v1.pos, i);
	f2 = geo_subv4(((t_triangle*)(obj->content))->v2.pos, i);
	f3 = geo_subv4(((t_triangle*)(obj->content))->v3.pos, i);

	bary.x = geo_lenv4(geo_crossv4(f2, f3)) / geo_lenv4(rt_triangle_normale(obj, &i));
	bary.y = geo_lenv4(geo_crossv4(f3, f1)) / geo_lenv4(rt_triangle_normale(obj, &i));
	bary.z = geo_lenv4(geo_crossv4(f1, f2)) / geo_lenv4(rt_triangle_normale(obj, &i));
	bary = geo_normv4(bary);
	// bary.x = (double)geo_clamp((float)bary.x, 0.0, 1.0);
	// bary.y = (double)geo_clamp((float)bary.y, 0.0, 1.0);
	// bary.z = (double)geo_clamp((float)bary.z, 0.0, 1.0);
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
