/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 10:45:12 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/19 19:31:53 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cyl.h"

static int		rt_cyl_solve(t_cyl_inter *s, t_ray *r, t_v4d *v)
{
	double			t;
	double			delta_sqrt;
	double			sa2;

	s->delta = s->b * s->b - 4.0 * s->a * s->c;
	if (s->delta < 0.0)
		return (0);
	delta_sqrt = sqrt(s->delta);
	sa2 = s->a * 2.0;
	if (s->delta == 0.0)
		t = (-s->b - delta_sqrt) / sa2;
	else
	{
		s->sol1 = (-s->b - delta_sqrt) / sa2;
		s->sol2 = (s->b - delta_sqrt) / sa2;
		t = (s->sol1 < s->sol2 ? s->sol1 : s->sol2);
		t = (t < 0.0 ? s->sol1 : s->sol2);
		if (t < 0.0)
			return (0);
	}
	if (v)
		*v = (t_v4d){r->start.x + r->dir.x * t, r->start.y + r->dir.y * t, \
			r->start.z + r->dir.z * t, 0.0};
	r->lenght = t;
	return (1);
}

int				rt_cyl_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	t_cyl_inter		s;
	double			tmp[4];
	const t_v4d		*c = &obj->trans.w;
	const t_v4d		*rot = &obj->rotation;
	const double	radius = (double)((t_cyl*)obj->content)->radius;

	tmp[0] = rot->x * rot->x + rot->y * rot->y + rot->z * rot->z;
	tmp[1] = r->dir.x * rot->x + r->dir.y * rot->y + r->dir.z * rot->z;
	tmp[2] = (r->start.x - c->x) * (r->start.x - c->x) + (r->start.y - c->y) *
		(r->start.y - c->y) + (r->start.z - c->z) * (r->start.z - c->z);
	tmp[3] = rot->x * (r->start.x - c->x) + rot->y * (r->start.y - c->y) +
		rot->z * (r->start.z - c->z);
	s.a = (r->dir.x * r->dir.x + r->dir.y * r->dir.y + r->dir.z * r->dir.z) -
		((tmp[1] * tmp[1]) / tmp[0]);
	s.b = 2.0 * (r->dir.x * (r->start.x - c->x) + r->dir.y * (r->start.y - c->y)
			+ r->dir.z * (r->start.z - c->z)) - (2 * tmp[1] * tmp[3] / tmp[0]);
	s.c = tmp[2] - (radius * radius) - ((tmp[3] * tmp[3]) / tmp[0]);
	return (rt_cyl_solve(&s, r, v));
}

t_v4d			rt_cyl_normale(t_obj *obj, t_v4d *v)
{
	const t_v4d		*c = &obj->trans.w;

	return (draw_v4d_norm((t_v4d){
		v->x - c->x,
		2 * (v->y - c->y),
		2 * (v->z - c->z) - 1,
		1.0}));
}
