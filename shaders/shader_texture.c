/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 18:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/09/14 14:50:32 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "shaders.h"
#include "texture.h"
#include "mesh.h"
#include "sda.h"

static t_v2f inline	shader_texture_uv_sphere(const t_render *r)
{
	return ((t_v2f){
		(float)(0.5 + (atan2(r->normal.z, r->normal.x) / (2.0 * M_PI))),
		(float)(0.5 - (asin(r->normal.y) / M_PI))
	});
}

static inline t_v2f	shader_texture_uv_generic(const t_render *r)
{
	return ((t_v2f){
		(float)fabs((double)((int)(((r->normal.x != 0.0 ? r->intersection.z :
		r->intersection.x) * 1.0) * 1000.0) % 1000) * 0.001),
		(float)fabs((double)((int)(((r->normal.y != 0.0 ? r->intersection.z :
		r->intersection.y) * 1.0) * 1000.0) % 1000) * 0.001)
	});
}

static inline t_v2f	shader_texture_uv_triangle(const t_render *r)
{
	return (get_uv_triangle(r->obj_intersect, r->intersection));
}

unsigned int		shader_color_texture_intersection(const t_render *r)
{
	const t_texture			*tex = rt_obj_get_texture(r->obj_intersect);
	t_v2f					uv;
	unsigned int			(*uv_func)(SDL_Surface*, t_v2f);
	int						p;
	const t_shader_uvfunc	x[2] = {
		(t_shader_uvfunc){SPHERE, &shader_texture_uv_sphere},
		(t_shader_uvfunc){TRIANGLE, &shader_texture_uv_triangle}
	};

	uv = (t_v2f){0.0, 0.0};
	if ((p = 2) && ((!tex) || (!tex->surface->pixels)))
	{
		return ((r->obj_intersect->cfgbits & SDB_COLOR ?
			((t_cube*)r->obj_intersect->content)->color : 0));
	}
	while ((p--) && (!(x[p].type & r->obj_intersect->type)))
		;
	uv = (p < 0) ? shader_texture_uv_generic(r) : x[p].uv(r);
	uv_func = &draw_suv;
	if (r->obj_intersect->cfgbits & SDB_COLOR)
	{
		return (blend_add(uv_func(tex->surface, uv),
			((t_cube*)r->obj_intersect->content)->color));
	}
	return (uv_func(tex->surface, uv));
}

void				shader_texture(t_shader *s, t_render *r, t_obj *light,
		unsigned int *color_render)
{
	(void)light;
	(void)s;
	if (r->obj_intersect->cfgbits & SDB_TEXTURE)
		*color_render = shader_color_texture_intersection(r);
	else
		*color_render = ((t_cube*)(r->obj_intersect->content))->color;
}
