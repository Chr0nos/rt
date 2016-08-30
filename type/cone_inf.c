/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_inf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:30:00 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/30 17:12:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sphere.h"

static int		rt_cone_inf_solve(t_sphere_inter *s, t_ray *r, t_v4d *v)
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

int				rt_cone_inf_inter(t_obj *obj, t_ray *r, t_intersect *v)
{
	t_sphere_inter	s;
	t_v4d			v_sub;
	const t_v4d		c = obj->trans.w;
	t_v4d			rot;
	double			calc_size;

	calc_size = 1 + (double)((t_cone_inf*)obj->content)->size
		* (double)((t_cone_inf*)obj->content)->size;
	rot = geo_normv4((t_v4d){obj->rotation.x, obj->rotation.y,
		obj->rotation.z, obj->rotation.w});
	v_sub = (t_v4d){r->start.x - c.x, r->start.y - c.y, r->start.z - c.z, 1};
	s.a = geo_dotv4(r->dir, r->dir) - (calc_size * geo_dotv4(r->dir, rot)
			* geo_dotv4(r->dir, rot));
	s.b = 2 * (geo_dotv4(r->dir, v_sub) - (calc_size *
				geo_dotv4(r->dir, rot) * geo_dotv4(v_sub, rot)));
	s.c = geo_dotv4(v_sub, v_sub) - (calc_size * geo_dotv4(v_sub, rot)
			* geo_dotv4(v_sub, rot));
	return (rt_cone_inf_solve(&s, r, &v->in));
}

t_v4d			rt_cone_inf_normale(t_obj *obj, t_v4d *v)
{
	double		t;
	t_v4d		r;

	t = (-obj->trans.y.x * obj->trans.w.x - obj->trans.y.y * obj->trans.w.y
			- obj->trans.y.z * obj->trans.w.z + v->x * obj->trans.y.x + v->y *
			obj->trans.y.y + v->z * obj->trans.y.z) / (pow(obj->trans.y.x, 2) +
				pow(obj->trans.y.y, 2) + pow(obj->trans.y.z, 2));
	r = (t_v4d){v->x - (obj->trans.w.x + obj->trans.y.x * t),
		v->y - (obj->trans.w.y + obj->trans.y.y * t),
		v->z - (obj->trans.w.z + obj->trans.y.z * t),
		0.0};
	return (geo_normv4(r));
}
