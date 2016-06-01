/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 21:03:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/01 20:34:28 by alhote           ###   ########.fr       */
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
	double	tmax;

	tmax = (double)INFINITY;
	if ((tmax = check(box->xmin, box->xmax, r->start.x, r->dir.x)) == 0.0)
		return (0);
	if ((tmax = check(box->ymin, box->ymax, r->start.y, r->dir.y)) == 0.0)
		return (0);
	if ((tmax = check(box->zmin, box->zmax, r->start.z, r->dir.z)) == 0.0)
		return (0);
	if (tmax < 0.0)
		return (0);
	return (1);
}

void			rt_box_update(t_obj *obj)
{
	const t_v3f		*p = &obj->trans.offset;
	float			r;

	if (obj->type == CUBE)
	{
		r = ((t_cube*)(obj->content))->size / 2;
		obj->hitbox = (t_box){p->x - r, p->x + r, p->y - r, p->y + r,
			p->z - r, p->z + r};
	}
	else if (obj->type == SPHERE)
	{
		r = ((t_sphere*)(obj->content))->radius;
		obj->hitbox = (t_box){p->x - r, p->x + r, p->y - r, p->y + r,
			p->z - r, p->z + r};
	}
	else
		obj->hitbox = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	obj->bounds = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
}
