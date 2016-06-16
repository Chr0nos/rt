/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 18:01:31 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/16 17:25:30 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		set_value(double *tmin, double *tmax, double a, double b)
{
	*tmin = a;
	*tmax = b;
	if (*tmin > *tmax)
		draw_swap(tmin, tmax);
}

static int		height_value(double dir, t_v4d ab, t_obj *obj, double *tb)
{
	double		tmin;
	double		tmax;

	tmax = ab.x;
	tmin = tmax - (double)(((t_cone *)obj->content)->size);
	if ((int)dir)
	{
		tmin = tmin / dir;
		tmax = tmax / dir;
		if (tmin > tmax)
			draw_swap(&tmin, &tmax);
	}
	else if ((tmin > 0.0) || (tmax < 0.0))
		return (1);
	else
	{
		tmin = (double)-INFINITY;
		tmax = (double)INFINITY;
	}
	if ((tmin > tb[1]) || (tmax < tb[0]))
		return (1);
	tb[0] = fmax(tb[0], tmin);
	tb[1] = fmin(tb[1], tmax);
	return (0);
}

static int		compute_value(double rdy, double dir, t_v4d ab, double *tb)
{
	double		tmin;
	double		tmax;

	if ((int)dir)
		set_value(&tmin, &tmax,
			ab.x - ab.y / (ab.z - rdy / dir),
			ab.x - ab.y / (-ab.z - rdy / dir));
	else
	{
		set_value(&tmin, &tmax, ab.y + ab.w * ab.x, ab.y - ab.w * ab.x);
		if ((tmin > 0.0) || (tmax < 0.0))
			return (1);
		tmin = (double)-INFINITY;
		tmax = (double)INFINITY;
	}
	if ((tmin > tb[1]) || (tmax < tb[0]))
		return (1);
	tb[0] = fmax(tb[0], tmin);
	tb[1] = fmin(tb[1], tmax);
	return (0);
}

int				rt_cone_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	const double	w = ((t_cone *)obj->content)->angle.w;
	t_v4d			ab;
	double			tb[2];

	tb[0] = (double)-INFINITY;
	tb[1] = (double)INFINITY;
	ab = (t_v4d){r->start.y - obj->trans.w.y,
		r->start.x - obj->trans.w.x, 1.0 / w, w};
	if (compute_value(r->dir.y, r->dir.x, ab, tb))
		return (0);
	ab.y = r->start.z - obj->trans.w.z;
	if (compute_value(r->dir.y, r->dir.z, ab, tb))
		return (0);
	if (height_value(r->dir.y, ab, obj, tb))
		return (0);
	r->lenght = (tb[0] >= 0.0) ? tb[0] : tb[1];
	if (v)
		*v = (t_v4d){
			r->start.x + r->dir.x * r->lenght,
			r->start.y + r->dir.y * r->lenght,
			r->start.z + r->dir.z * r->lenght,
			0.0
		};
	return (1);
}

t_v4d			rt_cone_normale(t_obj *obj, t_v4d *v)
{
	(void)v;
	return (draw_v4d_norm(obj->trans.y));
}
