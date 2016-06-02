/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 21:03:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/01 21:48:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	check(float min, float max, float start, float dir)
{
	double	tmin;
	double	tmax;
	double	temp[2];

	tmin = (double)-INFINITY;
	tmax = (double)INFINITY;
	if (dir != 0.0f)
	{
		temp[0] = (double)((min - start) / dir);
		temp[1] = (double)((max - start) / dir);
		tmin = fmax(tmin, fmin(temp[0], temp[1]));
		tmax = fmin(tmax, fmax(temp[0], temp[1]));
		if (tmin > tmax)
			return (0.0);
	}
	return (tmax);
}

int				raybox_check(t_ray *r, t_box *box)
{
	double			tmax;
	const float		rx = (float)r->dir.x;
	const float		ry = (float)r->dir.y;
	const float		rz = (float)r->dir.z;

	tmax = (double)INFINITY;
	if ((tmax = check(box->xmin, box->xmax, rx, rx)) == 0.0)
		return (0);
	if ((tmax = check(box->ymin, box->ymax, ry, ry)) == 0.0)
		return (0);
	if ((tmax = check(box->zmin, box->zmax, rz, rz)) == 0.0)
		return (0);
	if (tmax < 0.0)
		return (0);
	return (1);
}

void			rt_box_update(t_obj *obj)
{
	const t_v4f		p = draw_convert_v4d_to_v4f(obj->trans.w);
	float			r;

	if (obj->type == CUBE)
	{
		r = ((t_cube*)(obj->content))->size / 2.0f;
		obj->hitbox = (t_box){p.x - r, p.x + r, p.y - r, p.y + r,
			p.z - r, p.z + r};
	}
	else if (obj->type == SPHERE)
	{
		r = ((t_sphere*)(obj->content))->radius;
		obj->hitbox = (t_box){p.x - r, p.x + r, p.y - r, p.y + r,
			p.z - r, p.z + r};
	}
	else
		obj->hitbox = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	obj->bounds = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
}
