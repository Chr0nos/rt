/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 10:45:12 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/13 14:06:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cyl.h"

static int		rt_cyl_solve(t_cyl_inter *s, t_ray *r, t_v4d *v)
{
	(void)s;
	(void)r;
	(void)v;
	return (0);
}

int				rt_cyl_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	t_cyl_inter	s;
	const t_v4d		*c = &obj->trans.w;
	const double	radius = (double)((t_cyl*)obj->content)->radius;

	s.a = r->dir.x * r->dir.x + r->dir.y * r->dir.y + r->dir.z * r->dir.z;
	s.b = 2.0 * (r->dir.x * (r->start.x - c->x) +
		r->dir.y * (r->start.y - c->y)
		+ r->dir.z * (r->start.z - c->z));
	s.c = (((r->start.x - c->x) * (r->start.x - c->x)) +
	((r->start.y - c->y) * (r->start.y - c->y)) + ((r->start.z - c->z) *
	(r->start.z - c->z))) - radius * radius;
	return (rt_cyl_solve(&s, r, v));
}

t_v4d			rt_cyl_normale(t_obj *obj, t_v4d *v)
{
	const t_v4d		*c = &obj->trans.w;

	return (draw_v4d_norm((t_v4d){v->x - c->x, v->y - c->y, v->z - c->z, 1.0}));
}
