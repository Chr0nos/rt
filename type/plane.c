/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 19:00:18 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/02 03:01:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			rt_plane_inter(t_obj *obj, t_ray *r, t_intersect *v)
{
	const t_v4d		plane = obj->trans.y;
	double			t;

	t = geo_dotv4(plane, r->dir);
	if (t == 0.0)
		return (0);
	t = -geo_dotv4(plane, geo_subv4(r->start, obj->trans.w)) / t;
	if (t < 0.0)
		return (0);
	if (v)
	{
		v->in = (t_v4d){
			r->start.x + r->dir.x * t,
			r->start.y + r->dir.y * t,
			r->start.z + r->dir.z * t,
			0.0
		};
		v->len_in = t;
		v->len_out = (double)INFINITY;
		v->flags = INTER_IN;
	}
	r->lenght = t;
	return (1);
}

t_v4d		rt_plane_normale(t_obj *obj, t_v4d *v)
{
	(void)v;
	return (obj->trans.y);
}
