/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 21:03:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/01 13:59:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		raybox_check(t_ray *r, t_box *box)
{
	double	tmin;
	double	tmax;
	double	temp[2];

	tmin = (double)-INFINITY;
	tmax = (double)INFINITY;
	if (r->dir.x != 0.0f)
	{
		temp[0] = (double)((box->xmin - r->start.x) / r->dir.x);
		temp[1] = (double)((box->xmax - r->start.x) / r->dir.x);
		tmin = fmax(tmin, fmin(temp[0], temp[1]));
		tmax = fmin(tmax, fmax(temp[0], temp[1]));
		if (tmin > tmax)
			return (0);
	}
	if (r->dir.y != 0.0f)
	{
		temp[0] = (double)((box->ymin - r->start.y) / r->dir.y);
		temp[1] = (double)((box->ymax - r->start.y) / r->dir.y);
		tmin = fmax(tmin, fmin(temp[0], temp[1]));
		tmax = fmin(tmax, fmax(temp[0], temp[1]));
		if (tmin > tmax)
			return (0);
	}
	if (r->dir.z != 0.0f)
	{
		temp[0] = (double)((box->zmin - r->start.z) / r->dir.z);
		temp[1] = (double)((box->zmax - r->start.z) / r->dir.z);
		tmin = fmax(tmin, fmin(temp[0], temp[1]));
		tmax = fmin(tmax, fmax(temp[0], temp[1]));
		if (tmin > tmax)
			return (0);
	}
	if (tmax < 0.0)
		return (0);
	return (1);
}

void	rt_box_update(t_obj *obj)
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
