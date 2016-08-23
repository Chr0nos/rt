/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 18:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/08/23 14:26:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "shaders.h"
#include "texture.h"
#include "libft.h"
#include "mesh.h"
#include "sda.h"

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
		uv = get_uv_triangle(r->obj_intersect, r->intersection);
	else
	{
		uv = (t_v2f){
			(float)fabs((double)((int)(((r->normal.x != 0.0 ? r->intersection.z :
			r->intersection.x) * 1.0) * 1000.0) % 1000) * 0.001),
			(float)fabs((double)((int)(((r->normal.y != 0.0 ? r->intersection.z :
			r->intersection.y) * 1.0) * 1000.0) % 1000) * 0.001)
		};
	}
	if (r->obj_intersect->cfgbits & SDB_COLOR)
		return (blend_add(draw_suv_smooth(tex->surface, uv),
			((t_cube*)r->obj_intersect->content)->color));
	return (draw_suv_smooth(tex->surface, uv));
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
