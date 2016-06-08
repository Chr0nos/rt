/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 19:00:18 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/08 19:43:27 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rt_plane_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	const t_v4d		inv = draw_v4d_inv(obj->trans.w);
	const double	t = draw_v4d_dot(inv,
		draw_v4d_sub(r->start, obj->trans.w)) /
		draw_v4d_dot(obj->trans.w, r->dir);

	if (t < 0.0)
		return (0);
	if (v)
		*v = (t_v4d){
			r->start.x + r->dir.x * t,
			r->start.y + r->dir.y * t,
			r->start.z + r->dir.z * t,
			0.0
		};
	return (1);
}

t_v4d	rt_plane_normale(t_obj *obj, t_v4d *v)
{
	(void)v;
	return (draw_v4d_norm(obj->trans.w));
}
