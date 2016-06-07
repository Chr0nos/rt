/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 19:04:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/08 00:30:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "render.h"

int			rt_render_foreach(t_obj *obj, int mode, void *userdata)
{
	t_render	*r;

	(void)mode;
	r = userdata;
	if (!(obj->type & VISIBLE))
		return (OK);
	if (!raybox_check(r->ray, &obj->bounds))
		return (STOP_NODE);
	if (raybox_check(r->ray, &obj->hitbox))
	{
		if (r->lowest_lenght < r->ray->lenght)
			return (OK);
		r->lowest_lenght = r->ray->lenght;
		if (obj->type == CUBE)
			r->ray->color = ((t_cube*)obj->content)->color;
		else if (obj->type == SPHERE)
			r->ray->color = ((t_sphere*)obj->content)->color;
		else
			r->ray->color = COLOR_WHITE;
		return (OK);
	}
	return (OK);
}

t_uint		rt_render(t_rt *rt, t_ray *ray)
{
	t_render	r;

	ray->lenght = HUGE_VAL;
	r = (t_render){ray, HUGE_VAL};
	ray->color = COLOR_BLACK;
	rt_node_foreach(rt->root, INFIX, &rt_render_foreach, &r);
	ray->lenght = r.lowest_lenght;
	return (ray->color);
}
