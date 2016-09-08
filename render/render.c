/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 19:04:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/08 22:56:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "render.h"
#include "shaders.h"
#define PI_INV 1.0 / M_PI
#define PI2_INV 1.0 / (2.0 * M_PI)

static unsigned int	get_background_color(t_render *r)
{
	const t_texture		*tex = r->rt->settings.skybox;
	unsigned int		*pixels_texture;
	double				u;
	double				v;

	if (!(pixels_texture = (tex) ? tex->surface->pixels : NULL))
		return (r->rt->settings.bgcolor);
	u = 0.5 + (atan2(r->ray->dir.z, r->ray->dir.x) * PI2_INV);
	v = 0.5 - (asin(r->ray->dir.y) * PI_INV);
	return (pixels_texture[tex->surface->w *
			(int)(v * tex->surface->h) + (int)(u * tex->surface->w)]);
}

int					rt_render_foreach(t_obj *obj, int mode, void *userdata)
{
	t_render		*r;
	t_intersect		impact;

	(void)mode;
	impact = (t_intersect){0.0, 0.0, geo_dtov4d(0.0), geo_dtov4d(0.0), 0};
	r = userdata;
	if ((!(obj->type & NOCHECKBOX)) &&
		(!raybox_cube_check(r->ray, &obj->bounds)))
		return (STOP_NODE);
	if ((obj->type & NOCHECKBOX) || (raybox_cube_check(r->ray, &obj->hitbox)))
	{
		IFRET__(!(obj->type & VISIBLE), OK);
		if ((obj->inters) && (obj->inters(obj, r->ray, &impact) == 0))
			;
		else
			rt_render_nocsg(obj, r, &impact);
	}
	return (OK);
}

static void			init_colors(unsigned int *colors, t_shader *shader)
{
	int				i;

	i = 0;
	while (shader)
	{
		if (shader->enabled)
			colors[i++] = shader->color_render;
		shader = shader->next;
	}
}

unsigned int		rt_render_ray(t_rt *rt, t_ray *ray)
{
	t_render		r;
	unsigned int	colors[MAX_SHADERS];

	r = (t_render){
		ray, rt, NULL, HUGE_VAL, 0.0,
		(t_v4d){0.0, 0.0, 0.0, 0.0},
		ray->dir,
		(unsigned int*)colors
	};
	ray->color = 0xff000000;
	rt_node_foreach(rt->tree.bounded, INFIX, &rt_render_foreach, &r);
	rt_node_foreach(rt->tree.unbounded, INFIX, &rt_render_foreach, &r);
	if (r.obj_intersect)
	{
		init_colors((unsigned int*)colors, r.obj_intersect->shader->shader);
		r.normal = r.obj_intersect->normal(r.obj_intersect, &(r.intersection));
		r.ray->color = 0xFFFFFF00;
		rt_node_foreach(rt->tree.light, INFIX, &rt_render_light, &r);
		r.ray->color = shaders_compute_color(r.obj_intersect->shader,
				0xff000000, (unsigned int *)colors);
		r.ray->count--;
	}
	else
		return (get_background_color(&r));
	return (rt_render_opacity(rt, ray, &r));
}

void				rt_render(t_rt *rt)
{
	rt_init_rt_rendermode(rt, &rt_rays);
}
