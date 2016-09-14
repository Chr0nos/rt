/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_normalmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 15:27:09 by alhote            #+#    #+#             */
/*   Updated: 2016/09/14 14:50:03 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "shaders.h"
#include "texture.h"
#include "libft.h"
#include "mesh.h"

static t_v2f	shader_normalmap_uv(const t_render *r)
{
	return ((t_v2f){
		(float)fabs((double)((int)(((r->normal.x != 0.0 ? r->intersection.z :
		r->intersection.x) * 1.0) * 1000.0) % 1000) * 0.001),
		(float)fabs((double)((int)(((r->normal.y != 0.0 ? r->intersection.z :
		r->intersection.y) * 1.0) * 1000.0) % 1000) * 0.001)});
}

unsigned int	shader_color_normal_intersection(const t_render *r)
{
	const t_texture		*tex = rt_obj_get_normal(r->obj_intersect);
	const unsigned int	*pixels_texture = (tex) ? tex->surface->pixels : NULL;
	t_v2f				uv;

	if (!pixels_texture)
		return (0);
	uv = (t_v2f){0.0, 0.0};
	if (r->obj_intersect->type & SPHERE)
	{
		uv = (t_v2f){
			(float)(0.5 + (atan2(r->normal.z, r->normal.x) / (2.0 * M_PI))),
			(float)(0.5 - (asin(r->normal.y) / M_PI))
		};
	}
	else if (r->obj_intersect->type & TRIANGLE)
		uv = get_uv_triangle(r->obj_intersect, r->intersection);
	else
		uv = shader_normalmap_uv(r);
	return (draw_suv(tex->surface, uv));
}

void			shader_normalmap(t_shader *s, t_render *r, t_obj *light,
		unsigned int *color_render)
{
	t_v4d				transformation_vector;
	unsigned int		color_normal;

	(void)light;
	(void)s;
	(void)color_render;
	color_normal = shader_color_normal_intersection(r);
	if (color_normal)
	{
		transformation_vector = geo_subv4(r->normal,
				(t_v4d){0.0, 0.0, -1.0, 1.0});
		r->normal = geo_normv4(geo_addv4(geo_normv4(
			(t_v4d){(double)R(color_normal) - 128.0,
			(double)G(color_normal) - 128.0,
			(double)-(B(color_normal) - 128.0), 1.0}),
			transformation_vector));
	}
}
