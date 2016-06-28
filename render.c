/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 19:04:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/28 13:30:42 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "render.h"
#include "shaders.h"

int				rt_shadow_foreach(t_obj *obj, int mode, void *userdata)
{
	t_render	*r;

	(void)mode;
	r = userdata;
	if (obj == r->obj_intersect)
		return (OK);
	if ((!(obj->type & NOCHECKBOX)) && (!raybox_check(r->ray, &obj->bounds)))
	{
		return (STOP_NODE);
	}
	if ((obj->type & NOCHECKBOX) || (raybox_check(r->ray, &obj->hitbox)))
	{
		if ((obj->inters) && (obj->inters(obj, r->ray, NULL) == 0))
			;
		else if (r->light_lenght < r->ray->lenght)
			;
		else
		{
			r->light_power = 0.0;
			r->specular_power = 0.0;
			return (STOP_ALL);
		}
	}
	return (OK);
}

/*
** called on EACH spot
** by rt_render_foreach
*/

int				rt_light_foreach(t_obj *obj, int mode, void *userdata)
{
	t_render	*r;
	t_ray		origin;
	t_v2d		lor;

	(void)mode;
	r = userdata;
	origin = *r->ray;
	lor = (t_v2d){r->light_power, r->specular_power};
	exec_fshaders(r->obj_intersect->shader, r, obj);
	if ((r->light_power + r->specular_power > 0.0)
		&& (r->ray->lenght > 0.000005))
	{
		rt_node_foreach(r->rt->tree.bounded, INFIX, &rt_shadow_foreach, r);
		rt_node_foreach(r->rt->tree.unbounded, INFIX, &rt_shadow_foreach, r);
	}
	r->light_power += lor.x;
	r->specular_power += lor.y;
	*r->ray = origin;
	return (OK);
}

int				rt_render_foreach(t_obj *obj, int mode, void *userdata)
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
		if ((obj->inters) && (obj->inters(obj, r->ray, &impact) == 0))
			;
		else if (r->lowest_lenght < r->ray->lenght)
			;
		else
		{
			r->intersection = impact;
			r->lowest_lenght = r->ray->lenght;
			r->ray->color = ((t_cube*)obj->content)->color;
			r->obj_intersect = obj;
		}
	}
	return (OK);
}

unsigned int	rt_render_opacity(t_rt *rt, const t_ray *ray, const t_render *r)
{
	unsigned char			alpha;
	t_ray					nray;
	double					cos0[2];
	double					coef;

	if (!r->obj_intersect)
		return (ray->color);
	alpha = (((t_cube*)r->obj_intersect->content)->color & 0xff000000) >> 24;
	if (!alpha)
		return (ray->color);
	nray = *ray;
	nray.start = geo_addv4(r->intersection, geo_multv4(ray->dir,
		geo_dtov4d(0.01)));
	cos0[0] = geo_dotv4(r->normal, geo_invv4(ray->dir));
	cos0[1] = sqrt(1 - pow(1.0 / r->obj_intersect->refractive_index, 2.0) *
			(1 - pow(cos0[0], 2.0)));
	coef = (cos0[0] > 0.0 ? -1.0 : 1.0);
	nray.dir = (t_v4d) {
		(1.0 / r->obj_intersect->refractive_index) * ray->dir.x +
		((1.0 / r->obj_intersect->refractive_index) * cos0[0] + cos0[1] * coef)
		* r->normal.x, (1.0 / r->obj_intersect->refractive_index) * ray->dir.y
		+ ((1.0 / r->obj_intersect->refractive_index) * cos0[0] + cos0[1] *
		coef) * r->normal.y, (1.0 / r->obj_intersect->refractive_index) *
		ray->dir.z + ((1.0 / r->obj_intersect->refractive_index) * cos0[0] +
		cos0[1] * coef) * r->normal.z, 0.0 };
	return (draw_color_lerp(ray->color, rt_render(rt, &nray),
		(float)alpha / 255.0f));
}

t_uint			rt_render(t_rt *rt, t_ray *ray)
{
	t_render	r;

	r = (t_render){
		ray,
		rt,
		NULL,
		HUGE_VAL,
		0.0,
		(t_v4d){0.0, 0.0, 0.0, 0.0},
		ray->dir,
		0.0, 0.0
	};
	ray->color = COLOR_BLACK;
	rt_node_foreach(rt->tree.bounded, INFIX, &rt_render_foreach, &r);
	rt_node_foreach(rt->tree.unbounded, INFIX, &rt_render_foreach, &r);
	if (r.obj_intersect)
	{
		r.normal = r.obj_intersect->normal(r.obj_intersect, &(r.intersection));
		rt_node_foreach(rt->tree.light, INFIX, &rt_light_foreach, &r);
	}
	ray->lenght = r.lowest_lenght;
	ray->color = draw_color_lerp(draw_color_lerp(0x000000, r.ray->color,
		(float)(fmax((r.light_power) / MID_LIGHT_POWER,
			rt->settings.ambiant_light))), 0xffffff,
		(float)(r.specular_power / MID_LIGHT_POWER));
	//return (ray->color);
	return (rt_render_opacity(rt, ray, &r));
}
