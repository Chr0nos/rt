/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 19:04:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/05 21:48:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			rt_render_foreach(t_obj *obj, int mode, void *userdata)
{
	t_ray	*ray;

	(void)mode;
	ray = userdata;
	if (obj->type & (CAMERA | ROOT | EMPTY | SPOT | POINTLIGHT))
		return (OK);
	if (!raybox_check(ray, &obj->bounds))
		return (STOP_NODE);
	if (raybox_check(ray, &obj->hitbox))
	{
		if (obj->type == CUBE)
			ray->color = ((t_cube*)obj->content)->color;
		else if (obj->type == SPHERE)
			ray->color = ((t_sphere*)obj->content)->color;
		else
			ray->color = COLOR_WHITE;
		return (STOP_ALL);
	}
	return (OK);
}

t_uint		rt_render(t_rt *rt, t_ray *ray)
{
	ray->color = COLOR_BLACK;
	rt_node_foreach(rt->root, INFIX, &rt_render_foreach, ray);
	return (ray->color);
}
