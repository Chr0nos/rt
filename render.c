/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 19:04:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/15 14:16:49 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "render.h"

int			rt_shadow_foreach(t_obj *obj, int mode, void *userdata)
{
	t_render	*r;

	(void)mode;
	r = userdata;
	if (!(obj->type & VISIBLE) || obj == r->obj_intersect)
		return (OK);
	if ((!(obj->type & NOCHECKBOX)) && (!raybox_check(r->ray, &obj->bounds)))
		return (STOP_NODE);
	if ((obj->type & NOCHECKBOX) || (raybox_check(r->ray, &obj->hitbox)))
	{
		if ((obj->inters) && (obj->inters(obj, r->ray, NULL) == 0))
			return (OK);
		if (r->light_lenght < r->ray->lenght && r->ray->lenght > 0.000001)
			return (OK);
		r->ray->color = (r->ray->color >> 1) & 0x7f7f7f;
		return (STOP_ALL);
	}
	return (OK);
}

/*
** called on EACH spot
** by rt_render_foreach
*/

int			rt_light_foreach(t_obj *obj, int mode, void *userdata)
{
	t_render	*r;
	t_ray		origin;

	(void)mode;
	if (!(obj->type & (POINTLIGHT | SPOT)))
		return (OK);
	r = userdata;
	origin = *r->ray;
	r->ray->start = r->intersection;
	r->light_lenght = draw_v4d_dist(obj->trans.w, r->ray->start);
	r->ray->dir = draw_v4d_norm(draw_v4d_sub(obj->trans.w, r->ray->start));
	rt_node_foreach(r->root, INFIX, &rt_shadow_foreach, r);
	origin.color = r->ray->color;
	*r->ray = origin;
	return (OK);
}

int			rt_render_foreach(t_obj *obj, int mode, void *userdata)
{
	t_render	*r;

	(void)mode;
	r = userdata;
	if (!(obj->type & VISIBLE))
		return (OK);
	if ((!(obj->type & NOCHECKBOX)) && (!raybox_check(r->ray, &obj->bounds)))
		return (STOP_NODE);
	if ((obj->type & NOCHECKBOX) || (raybox_check(r->ray, &obj->hitbox)))
	{
		if ((obj->inters) && (obj->inters(obj, r->ray, &r->intersection) == 0))
			return (OK);
		if (r->lowest_lenght < r->ray->lenght)
			return (OK);
		r->lowest_lenght = r->ray->lenght;
		r->ray->color = ((t_cube*)obj->content)->color;
		if (obj->texture && ((int)(r->ray->lenght * 4) % 2))
			r->ray->color = r->ray->color / 2 ;
		r->obj_intersect = obj;
	}
	return (OK);
}

t_uint		rt_render(t_rt *rt, t_ray *ray)
{
	t_render	r;

	r = (t_render){
		ray,
		rt->root,
		NULL,
		HUGE_VAL,
		0.0,
		(t_v4d){0.0, 0.0, 0.0, 0.0}
	};
	ray->color = COLOR_BLACK;
	rt_node_foreach(rt->root, INFIX, &rt_render_foreach, &r);
	if (r.obj_intersect)
		rt_node_foreach(rt->root, INFIX, &rt_light_foreach, &r);
	ray->lenght = r.lowest_lenght;
	return (ray->color);
}
