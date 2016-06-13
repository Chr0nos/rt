/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 18:01:31 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/13 10:33:30 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rt_cone_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	const double	c = r->dir.x * r->dir.x + r->dir.y * r->dir.y
		- r->dir.z * r->dir.z;
	const double	b = draw_v4d_dot((t_v4d){2.0, 2.0, -2.0, 1.0},
			draw_v4d_mult(r->start, r->dir));
	double			t;

	*v = (t_v4d){r->start.x - obj->trans.w.x,
		r->start.y - obj->trans.w.x, r->start.z - obj->trans.w.x, 1.0};
	t = draw_v4d_dot(*v, draw_v4d_mult((t_v4d){1.0, 1.0, -1.0, 1.0}, *v));
	t = (-b + sqrt(b * b - 4.0 * t * c)) / (2 * t);
	if (t < 0.0)
		return (0);
	if (v)
		*v = (t_v4d){
			r->start.x + r->dir.x * t,
				r->start.y + r->dir.y * t,
				r->start.z + r->dir.z * t,
				0.0
		};
	r->lenght = t;
	return (1);
}

t_v4d	rt_cone_normale(t_obj *obj, t_v4d *v)
{
	(void)v;
	return (draw_v4d_norm(obj->trans.y));
}
