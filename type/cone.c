/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 18:01:31 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/16 19:04:25 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// static void		set_value(double *tmin, double *tmax, double a, double b)
// {
// 	*tmin = a;
// 	*tmax = b;
// 	if (*tmin > *tmax)
// 		draw_swap(tmin, tmax);
// }
//
// static int		height_value(double dir, t_v4d ab, t_obj *obj, double *tb)
// {
// 	double		tmin;
// 	double		tmax;
//
// 	tmax = ab.x;
// 	tmin = tmax - (double)(((t_cone *)obj->content)->size);
// 	if ((int)dir)
// 	{
// 		tmin = tmin / dir;
// 		tmax = tmax / dir;
// 		if (tmin > tmax)
// 			draw_swap(&tmin, &tmax);
// 	}
// 	else if ((tmin > 0.0) || (tmax < 0.0))
// 		return (1);
// 	else
// 	{
// 		tmin = (double)-INFINITY;
// 		tmax = (double)INFINITY;
// 	}
// 	if ((tmin > tb[1]) || (tmax < tb[0]))
// 		return (1);
// 	tb[0] = fmax(tb[0], tmin);
// 	tb[1] = fmin(tb[1], tmax);
// 	return (0);
// }
//
// static int		compute_value(double rdy, double dir, t_v4d ab, double *tb)
// {
// 	double		tmin;
// 	double		tmax;
//
// 	if ((int)dir)
// 		set_value(&tmin, &tmax,
// 			ab.x - ab.y / (ab.z - rdy / dir),
// 			ab.x - ab.y / (-ab.z - rdy / dir));
// 	else
// 	{
// 		set_value(&tmin, &tmax, ab.y + ab.w * ab.x, ab.y - ab.w * ab.x);
// 		if ((tmin > 0.0) || (tmax < 0.0))
// 			return (1);
// 		tmin = (double)-INFINITY;
// 		tmax = (double)INFINITY;
// 	}
// 	if ((tmin > tb[1]) || (tmax < tb[0]))
// 		return (1);
// 	tb[0] = fmax(tb[0], tmin);
// 	tb[1] = fmin(tb[1], tmax);
// 	return (0);
// }

int				rt_cone_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	const double	w = tan(((t_cone *)obj->content)->angle.x / 2.0);
	const t_v4d		e = draw_v4d_sub(r->start, obj->trans.w);
	double			t;
	t_v4d			ab;
	double			tb[2];

	(void)obj;
	tb[0] = (double)-INFINITY;
	tb[1] = (double)INFINITY;
	ab = (t_v4d){
		r->dir.x * r->dir.x + r->dir.z * r->dir.z - r->dir.y * r->dir.y * w,
		2.0 * e.x * r->dir.x + 2.0 * e.z * r->dir.z
			- 2.0 * e.y * r->dir.y * w,
		e.x * e.x + e.z * e.z
			- e.y * e.y * w,
		0.0};
	if (ab.x == 0.0)
		return (0);
	ab.w = sqrt((ab.y * ab.y) - (4.0 * ab.x * ab.z));
	tb[0] = (-ab.y + ab.w) / (2.0 * ab.x);
	tb[1] = (-ab.y - ab.w) / (2.0 * ab.x);
	if (tb[1] < tb[0])
		draw_swap(&tb[0], &tb[1]);
	if (tb[1] < 0.0)
		return (0);
	// ab = (t_v4d){r->start.y - obj->trans.w.y,
	// 	r->start.x - obj->trans.w.x, 1.0 / w, w};
	// if (compute_value(r->dir.y, r->dir.x, ab, tb))
	// 	return (0);
	// ab.y = r->start.z - obj->trans.w.z;
	// if (compute_value(r->dir.y, r->dir.z, ab, tb))
	// 	return (0);
	// if (height_value(r->dir.y, ab, obj, tb))
	// 	return (0);
	t = (tb[0] >= 0.0) ? tb[0] : tb[1];
	ab.x = r->start.y + r->dir.y * t;
	ab.y = obj->trans.w.y - (double)(((t_cone *)obj->content)->size);
	ab.z = obj->trans.w.y;
	ab.w = r->start.y + r->dir.y * tb[1];
	if ((ab.x < ab.y) || (ab.x > ab.z))
	{
		t = tb[1];
		if ((ab.w < ab.y) || (ab.w > ab.z))
			return (0);
	}
	r->lenght = t;
	if (v)
		*v = (t_v4d){
			r->start.x + r->dir.x * t,
			r->start.y + r->dir.y * t,
			r->start.z + r->dir.z * t,
			0.0
		};
	return (1);
}

t_v4d			rt_cone_normale(t_obj *obj, t_v4d *v)
{
	(void)v;
	return (draw_v4d_norm(obj->trans.y));
}
