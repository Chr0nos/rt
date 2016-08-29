/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 19:04:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/29 20:41:27 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "render.h"
#include "shaders.h"

static unsigned int	get_background_color(t_render *r)
{
	t_texture		*tex;
	unsigned int	*pixels_texture;
	double			u;
	double			v;

	if (!r->rt->settings.skybox)
		return (r->rt->settings.bgcolor);
	tex = r->rt->settings.skybox;
	pixels_texture = tex->surface->pixels;
	u = 0.5 + (atan2(r->ray->dir.z, r->ray->dir.x) / (2.0 * M_PI));
	v = 0.5 - (asin(r->ray->dir.y) / M_PI);
	return (pixels_texture[tex->surface->w *
		(int)(v * tex->surface->h) + (int)(u * tex->surface->w)]);
}


/*
** if the function return OK -> we draw the pixels
** in ANY other case: the object will not be showed
*/

static inline int	rt_render_csg(t_obj *obj, t_render *r, t_v4d *impact)
{
	const char		on = obj->flags & FLAG_CSG_NEGATIVE;
	const char		rn = r->ray->flags & FLAG_CSG_NEGATIVE;

	(void)impact;
	if (!r->obj_intersect)
	{
		r->obj_intersect = obj;
		r->ray->flags |= FLAG_CSG_NEGATIVE;
		return ((!on) ? OK : -1);
	}
	if ((!on) && (!rn))
		r->lowest_lenght = r->ray->lenght;
	if (r->obj_intersect == obj)
	{
		r->ray->flags ^= FLAG_CSG_NEGATIVE;
		return (OK);
	}
	if ((!on) && (!r->obj_intersect))
	{
		r->obj_intersect = obj;
		return (OK);
	}
	if (on)
	{
		if (obj == r->obj_intersect)
			return (OK);
		r->obj_intersect = obj;
	}
	//r->ray->start = geo_addv4(r->ray->start,
	//	geo_multv4(r->ray->dir, geo_multv4(r->ray->dir, geo_dtov4d(0.01))));
	//rt_node_foreach(r->rt->tree.bounded, PREFIX, &rt_render_foreach, r);
	return (-1);
}

int					rt_render_foreach(t_obj *obj, int mode, void *userdata)
{
	t_render	*r;
	t_v4d		impact;

	(void)mode;
	impact = (t_v4d){0.0, 0.0, 0.0, 0.0};
	r = userdata;
	if ((!(obj->type & NOCHECKBOX)) && (!raybox_check(r->ray, &obj->bounds)))
		return (STOP_NODE);
	if ((obj->type & NOCHECKBOX) || (raybox_check(r->ray, &obj->hitbox)))
	{
		IFRET__(!(obj->type & VISIBLE), OK);
		if ((obj->inters) && (obj->inters(obj, r->ray, &impact) == 0))
			;
		else if (r->lowest_lenght < r->ray->lenght)
			;
		else// if (rt_render_csg(obj, r, &impact) == OK)
		{
			(void)rt_render_csg;
			r->obj_intersect = obj;
			r->intersection = impact;
			r->lowest_lenght = r->ray->lenght;
		}
	}
	return (OK);
}

unsigned int		rt_render_ray(t_rt *rt, t_ray *ray)
{
	t_render	r;

	r = (t_render){
		ray, rt, NULL,
		HUGE_VAL,
		0.0,
		(t_v4d){0.0, 0.0, 0.0, 0.0},
		ray->dir
	};
	ray->flags = 0;
	ray->color = 0xff000000;
	rt_node_foreach(rt->tree.bounded, INFIX, &rt_render_foreach, &r);
	rt_node_foreach(rt->tree.unbounded, INFIX, &rt_render_foreach, &r);
	if ((r.obj_intersect) && (r.obj_intersect->flags & FLAG_CSG_NEGATIVE))
		r.obj_intersect = NULL;
	if (r.obj_intersect)
	{
		r.normal = r.obj_intersect->normal(r.obj_intersect, &(r.intersection));
		rt_node_foreach(rt->tree.light, INFIX, &rt_render_light, &r);
		r.ray->color = shaders_compute_color(r.obj_intersect->shader,
			0xff000000);
	}
	ray->lenght = r.lowest_lenght;
	if (!r.obj_intersect)
		return (get_background_color(&r));
	return (rt_render_opacity(rt, ray, &r));
}

unsigned int		rt_render_bray(t_rt *rt, t_ray *ray)
{
	t_render	r;

	r = (t_render){
		ray, rt,
		NULL,
		HUGE_VAL,
		0.0,
		(t_v4d){0.0, 0.0, 0.0, 0.0},
		ray->dir
	};
	ray->color = 0xff000000;
	rt_node_foreach(rt->tree.bounded, INFIX, &rt_render_foreach, &r);
	rt_node_foreach(rt->tree.unbounded, INFIX, &rt_render_foreach, &r);
	if (r.obj_intersect)
		r.ray->color = ((t_cube *)r.obj_intersect->content)->color;
	else
		return (get_background_color(&r));
	ray->lenght = r.lowest_lenght;
	return (rt_render_opacity(rt, ray, &r));
}

void				rt_render(t_rt *rt)
{
	if ((rt->settings.mode & MODE) == ALTERNATIVEMODE)
		rt_init_alterate_rendermode(rt, &rt_rays);
	else
		rt_init_rt_rendermode(rt, &rt_rays);
}
