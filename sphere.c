/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:40:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/08 18:08:38 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sphere.h"

static int		rt_sphere_solve(t_sphere_inter *s, t_ray *r, t_v4d *v)
{
	double			t;

	s->delta = s->b * s->b - 4.0 * s->a * s->c;
	if (s->delta < 0.0)
		return (0);
	else if (s->delta == 0.0)
		t = (-s->b - sqrt(s->delta)) / (2.0 * s->a);
	else
	{
		s->sol1 = (-s->b - sqrt(s->delta)) / (2.0 * s->a);
		s->sol2 = (s->b - sqrt(s->delta)) / (2.0 * s->a);
		t = (s->sol1 < s->sol2 ? s->sol1 : s->sol2);
		t = (t < 0.0 ? s->sol1 : s->sol2);
		if (t < 0.0)
			return (0);
	}
	if (v)
		*v = (t_v4d){
			r->start.x + r->dir.x * t,
			r->start.y + r->dir.y * t,
			r->start.z + r->dir.z * t,
			0.0
		};
	return (1);
}

int				rt_sphere_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	t_sphere_inter	s;
	const t_v4d		*c = &obj->trans.w;
	const double	radius = (double)((t_sphere*)obj->content)->radius;

	s.a = r->dir.x * r->dir.x + r->dir.y * r->dir.y + r->dir.z * r->dir.z;
	s.b = 2.0 * (r->dir.x * (r->start.x - c->x) +
		r->dir.y * (r->start.y - c->y)
		+ r->dir.z * (r->start.z - c->z));
	s.c = (((r->start.x - c->x) * (r->start.x - c->x)) +
	((r->start.y - c->y) * (r->start.y - c->y)) + ((r->start.z - c->z) *
	(r->start.z - c->z))) - radius * radius;
	return (rt_sphere_solve(&s, r, v));
}
