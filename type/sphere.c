/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:40:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/05 20:12:24 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sphere.h"

static void		rt_sphere_set_impact(const t_sphere_inter *s, const t_ray *r,
	t_intersect *v, char flags)
{
	v->in = geo_addv4(r->start, geo_multv4(r->dir, geo_dtov4d(s->sol1)));
	v->len_in = s->sol1;
	if (flags & INTER_OUT)
	{
		v->out = geo_addv4(r->start, geo_multv4(r->dir, geo_dtov4d(s->sol2)));
		v->len_out = s->sol2;
	}
	v->flags = flags;
}

static int		rt_sphere_solve(t_sphere_inter *s, t_ray *r, t_intersect *v)
{
	double			sa2;
	char			flags;

	r->lenght = HUGE_VAL;
	s->delta = s->b * s->b - 4.0 * s->a * s->c;
	if (s->delta < 0.0)
		return (0);
	s->delta_sqrt = sqrt(s->delta);
	sa2 = 1.0 / (s->a * 2.0);
	if ((s->delta == 0.0) && ((flags = INTER_IN)))
		s->sol1 = (-s->b - s->delta_sqrt) * sa2;
	else
	{
		s->sol1 = (-s->b - s->delta_sqrt) * sa2;
		s->sol2 = (s->b - s->delta_sqrt) * sa2;
		r->lenght = (geo_min(s->sol1, s->sol2) < 0.0) ? s->sol1 : s->sol2;
		if (r->lenght < 0.0)
			return (0);
		flags = INTER_IN | INTER_OUT;
	}
	if (v)
		rt_sphere_set_impact(s, r, v, flags);
	r->lenght = s->sol1;
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
	return (rt_sphere_solve(&s, r, v));
}

t_v4d			rt_sphere_normal(t_obj *obj, t_v4d *v)
{
	const t_v4d		*c = &obj->trans.w;

	if (!(obj->flags & FLAG_CSG_NEGATIVE))
		return (geo_normv4(geo_subv4(*v, *c)));
	return (geo_multv4(geo_normv4(geo_subv4(*v, *c)),
		(t_v4d){-1.0, -1.0, -1.0, 1.0}));
}
