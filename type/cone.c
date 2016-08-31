/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 18:01:31 by qloubier          #+#    #+#             */
/*   Updated: 2016/08/31 16:00:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		rt_cone_setv(t_intersect *v, t_ray *r, const double *tb)
{
	v->in = geo_addv4(r->start, geo_multv4(r->dir, geo_dtov4d(tb[0])));
	v->len_in = tb[0];
	v->flags = INTER_IN;
	if (tb[1] >= 0.0)
	{
		v->flags |= INTER_OUT;
		v->out = geo_addv4(r->start, geo_multv4(r->dir, geo_dtov4d(tb[1])));
		v->len_out = tb[1];
	}
}

static void		rt_cone_inter_init(t_v4d *ab, double *tb, t_ray *r, t_obj *obj)
{
	const t_v4d		e = geo_subv4(r->start, obj->trans.w);
	const double	w = tan(((t_cone *)obj->content)->angle.x / 2.0);

	tb[0] = (double)-INFINITY;
	tb[1] = (double)INFINITY;
	*ab = (t_v4d){
		r->dir.x * r->dir.x + r->dir.z * r->dir.z - r->dir.y * r->dir.y * w,
		2.0 * e.x * r->dir.x + 2.0 * e.z * r->dir.z - 2.0 * e.y * r->dir.y * w,
		e.x * e.x + e.z * e.z - e.y * e.y * w,
		0.0};
}

static int		rt_cone_inter_limit(t_v4d *ab, t_obj *obj, t_ray *r, double *tb)
{
	*ab = (t_v4d){
		r->start.y + r->dir.y * tb[0],
		obj->trans.w.y - (double)(((t_cone *)obj->content)->size),
		obj->trans.w.y,
		r->start.y + r->dir.y * tb[1]};
	if ((tb[0] < 0.0) || (ab->x < ab->y) || (ab->x > ab->z))
	{
		draw_swap(&tb[0], &tb[1]);
		if ((ab->w < ab->y) || (ab->w > ab->z))
			return (1);
	}
	return (0);
}

int				rt_cone_inter(t_obj *obj, t_ray *r, t_intersect *v)
{
	t_v4d			ab;
	double			tb[2];

	rt_cone_inter_init(&ab, tb, r, obj);
	if (ab.x == 0.0)
		return (0);
	ab.w = sqrt((ab.y * ab.y) - (4.0 * ab.x * ab.z));
	tb[0] = (-ab.y + ab.w) / (2.0 * ab.x);
	tb[1] = (-ab.y - ab.w) / (2.0 * ab.x);
	if (tb[1] < tb[0])
		draw_swap(&tb[0], &tb[1]);
	if ((tb[1] < 0.0) || (rt_cone_inter_limit(&ab, obj, r, tb)))
		return (0);
	r->lenght = tb[0];
	if (v)
		rt_cone_setv(v, r, tb);
	return (1);
}

t_v4d			rt_cone_normale(t_obj *obj, t_v4d *v)
{
	double		t;
	t_v4d		dir;
	double		beta;

	dir = obj->trans.y;
	beta = geo_dotv4(geo_normv4(geo_subv4(*v, obj->trans.w)), dir);
	if (acos(beta) * 180.0 / M_PI > 90.0)
	{
		dir = geo_multv4(dir, (t_v4d){-1.0, -1.0, -1.0, 1.0});
		beta = geo_dotv4(geo_normv4(geo_subv4(*v, obj->trans.w)), dir);
	}
	t = (geo_distv4(obj->trans.w, *v) * sin(beta)) / sin(1.5708 + beta);
	dir = geo_addv4(obj->trans.w, geo_multv4(dir, (t_v4d){t, t, t, 1.0}));
	return (geo_normv4(geo_subv4(*v, dir)));
}
