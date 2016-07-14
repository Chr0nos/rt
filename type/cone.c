/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 18:01:31 by qloubier          #+#    #+#             */
/*   Updated: 2016/07/14 17:08:51 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		rt_cone_setv(t_v4d *v, t_ray *r, const double *t)
{
	if (v)
		*v = (t_v4d){
			r->start.x + r->dir.x * *t,
			r->start.y + r->dir.y * *t,
			r->start.z + r->dir.z * *t,
			0.0
		};
}

static void		rt_cone_inter_init(t_v4d *ab, double *tb, t_ray *r, t_obj *obj)
{
	const t_v4d		e = geo_subv4(r->start, obj->trans.w);
	const double	w = tan(((t_cone *)obj->content)->angle.x / 2.0);

	tb[0] = (double)-INFINITY;
	tb[1] = (double)INFINITY;
	*ab = (t_v4d){
		r->dir.x * r->dir.x + r->dir.z * r->dir.z - r->dir.y * r->dir.y * w,
		2.0 * e.x * r->dir.x + 2.0 * e.z * r->dir.z
			- 2.0 * e.y * r->dir.y * w,
		e.x * e.x + e.z * e.z
			- e.y * e.y * w,
		0.0};
}

static int		rt_cone_inter_limit(t_v4d *ab, t_obj *obj, t_ray *r, double *tb)
{
	ab->x = r->start.y + r->dir.y * tb[0];
	ab->y = obj->trans.w.y - (double)(((t_cone *)obj->content)->size);
	ab->z = obj->trans.w.y;
	ab->w = r->start.y + r->dir.y * tb[1];
	if ((tb[0] < 0.0) || (ab->x < ab->y) || (ab->x > ab->z))
	{
		draw_swap(&tb[0], &tb[1]);
		if ((ab->w < ab->y) || (ab->w > ab->z))
			return (1);
	}
	return (0);
}

int				rt_cone_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	double			t;
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
	t = tb[0];
	r->lenght = t;
	rt_cone_setv(v, r, &t);
	return (1);
}

t_v4d			rt_cone_normale(t_obj *obj, t_v4d *v)
{
	// t_v4d		nor;
	// double		tmp;
	//
	// nor = geo_subv4(*v, obj->trans.w);
	// nor.y = 0.0;
	// nor = geo_normv4(nor);
	// tmp = ((t_cone *)obj->content)->angle.z;
	// nor = geo_multv4(nor, geo_dtov4d(1.0 - (tmp * tmp)));
	// nor.y = tmp;
	// return (nor);

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
	dir = geo_multv4(dir, (t_v4d){t, t, t, 1.0});
	dir = geo_addv4(obj->trans.w, dir);
	return (geo_normv4(geo_subv4(*v, dir)));
}
