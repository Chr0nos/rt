/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:40:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/30 16:45:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sphere.h"

static int		rt_sphere_solve(t_sphere_inter *s, t_ray *r, t_v4d *v)
{
	double			sa2;

	r->lenght = HUGE_VAL;
	s->delta = s->b * s->b - 4.0 * s->a * s->c;
	if (s->delta < 0.0)
		return (0);
	s->delta_sqrt = sqrt(s->delta);
	sa2 = 1.0 / (s->a * 2.0);
	if (s->delta == 0.0)
		s->sol = (-s->b - s->delta_sqrt) * sa2;
	else
	{
		s->sol1 = (-s->b - s->delta_sqrt) * sa2;
		s->sol2 = (s->b - s->delta_sqrt) * sa2;
		s->sol = (s->sol1 < s->sol2 ? s->sol1 : s->sol2);
		s->sol = (s->sol < 0.0 ? s->sol1 : s->sol2);
		if (s->sol < 0.0)
			return (0);
	}
	if (v)
		*v = geo_addv4(r->start, geo_multv4(r->dir, geo_dtov4d(s->sol)));
	r->lenght = s->sol;
	return (1);
}

int				rt_sphere_inter(t_obj *obj, t_ray *r, t_intersect *v)
{
	t_sphere_inter	s;
	const t_v4d		*c = &obj->trans.w;
	const t_v4d		tmp_c = geo_subv4(r->start, *c);
	const double	radius = (double)((t_sphere*)obj->content)->radius;

	s.a = geo_dotv4(r->dir, r->dir);
	s.b = 2.0 * geo_dotv4(r->dir, geo_subv4(r->start, *c));
	s.c = geo_dotv4(tmp_c, tmp_c) - radius * radius;
	return (rt_sphere_solve(&s, r, &v->in));
}

t_v4d			rt_sphere_normal(t_obj *obj, t_v4d *v)
{
	const t_v4d		*c = &obj->trans.w;

	return (geo_normv4((t_v4d){v->x - c->x, v->y - c->y, v->z - c->z, 1.0}));
}
