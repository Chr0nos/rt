/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 18:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/07/17 13:23:06 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "shaders.h"
#include "texture.h"
#include "libft.h"

unsigned int		shader_color_texture_intersection(const t_render *r)
{
	t_texture		*tex;
	unsigned int	*pixels_texture;
	double			u;
	double			v;

	tex = rt_obj_get_texture(r->obj_intersect);
	u = 0.0;
	v = 0.0;
	if (tex)
	{
		pixels_texture = tex->surface->pixels;
		u = fabs((double)((int)(((r->normal.x != 0.0 ? r->intersection.z :
			r->intersection.x) / 1.0) * 1000.0) % 1000) / 1000.0);
		v = fabs((double)((int)(((r->normal.y != 0.0 ? r->intersection.z :
			r->intersection.y) / 1.0) * 1000.0) % 1000) / 1000.0);
		if (r->obj_intersect->type & SPHERE)
		{
			u = 0.5 + (atan2(r->normal.z, r->normal.x) / (2.0 * M_PI));
			v = 0.5 - (asin(r->normal.y) / M_PI);
		}
		return (pixels_texture[tex->surface->w *
			(int)(v * tex->surface->h) + (int)(u * tex->surface->w)]);
	}
	else
		return (((t_cube*)(r->obj_intersect->content))->color);
}

void				shader_texture(t_shader *s, t_render *r, t_obj *light)
{
	(void)light;
	(void)s;
	s->color_render = shader_color_texture_intersection(r);
}
