/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 18:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/07/15 15:01:48 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "shaders.h"
#include "texture.h"
#include "libft.h"

void			shader_texture(t_shader *s, t_render *r, t_obj *light)
{
	t_texture		*tex;
	unsigned int	*pixels_texture;
	double			u;
	double			v;

	(void)light;
	(void)s;
	tex = rt_obj_get_texture(r->obj_intersect);
	u = 0.0;
	v = 0.0;
	if (tex)
	{
		pixels_texture = tex->surface->pixels;
		if (r->obj_intersect->type & PLAN)
		{
			u = (double)((int)((fabs(r->intersection.x) / 0.2) * 1000.0)
				% 1000) / 1000.0;
			v = (double)((int)((fabs(r->intersection.z) / 0.2) * 1000.0)
				% 1000) / 1000.0;
		}
		if (r->obj_intersect->type & SPHERE)
		{
			u = 0.5 + (atan2(r->normal.z, r->normal.x) / (2 * M_PI));
			v = 0.5 - (asin(r->normal.y) / M_PI);
		}
		s->color_render = pixels_texture[tex->surface->w *
			(int)(v * tex->surface->h) + (int)(u * tex->surface->w)];
	}
	else
		s->color_render = ((t_cube*)(r->obj_intersect->content))->color;
}
