/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_normalmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 15:27:09 by alhote            #+#    #+#             */
/*   Updated: 2016/07/16 15:36:15 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "shaders.h"
#include "texture.h"
#include "libft.h"

unsigned int			shader_color_normal_intersection(const t_render *r)
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
			u = 0.5 + (atan2(r->normal.z, r->normal.x) / (2 * M_PI));
			v = 0.5 - (asin(r->normal.y) / M_PI);
		}
		return (pixels_texture[tex->surface->w *
			(int)(v * tex->surface->h) + (int)(u * tex->surface->w)]);
	}
	else
		return (((t_cube*)(r->obj_intersect->content))->color);
}

void					shader_normalmap(t_shader *s, t_render *r, t_obj *light)
{
	t_v4d	transformation_vector;
	int		color_normal;

	(void)light;
	(void)s;
	color_normal = shader_color_normal_intersection(r);
	transformation_vector = geo_subv4(r->normal, (t_v4d){0.0, 0.0, -1.0, 1.0});
	r->normal = geo_addv(geo_normv4((t_v4d){(double)R(color_normal) - 128.0,
							(double)G(color_normal) - 128.0,
							(double)-(B(color_normal) - 128.0)}),
							transformation_vector);
}
