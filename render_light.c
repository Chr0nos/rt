/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 17:47:41 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/28 18:19:28 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rt.h"
#include "shaders.h"

/*
** called on EACH spot
** by rt_render_foreach
*/

int				rt_render_light(t_obj *obj, int mode, void *userdata)
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
		rt_node_foreach(r->rt->tree.bounded, INFIX, &rt_render_shadow, r);
		rt_node_foreach(r->rt->tree.unbounded, INFIX, &rt_render_shadow, r);
	}
	r->light_power += lor.x;
	r->specular_power += lor.y;
	*r->ray = origin;
	return (OK);
}
