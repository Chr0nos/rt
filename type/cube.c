/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 19:32:17 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 16:21:53 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "forms.h"
#include "cube.h"
#define CUBE_XMIN 0
#define CUBE_XMAX 1
#define CUBE_YMIN 2
#define CUBE_YMAX 3
#define CUBE_ZMIN 4
#define CUBE_ZMAX 5
#define CUBE_SIDES 6

static void			rt_cube_setintersect(t_ray *r, t_intersect *v, double *tb)
{
	v->len_in = tb[0];
	v->in = geo_addv4(r->start, geo_multv4(r->dir, geo_dtov4d(tb[0])));
	v->out = geo_addv4(r->start, geo_multv4(r->dir, geo_dtov4d(tb[1])));
	v->len_out = tb[1];
	v->flags = INTER_IN | (tb[1] < 0.0) ? 0 : INTER_OUT;
}

static inline int	rt_cube_inter_real(t_ray *r, t_box *box, t_intersect *v)
{
	t_cube_cmp		cube[3];
	double			tb[2];
	int				p;

	cube[0] = (t_cube_cmp){&(box->xmin), (float)r->start.x, (float)r->dir.x};
	cube[1] = (t_cube_cmp){&(box->ymin), (float)r->start.y, (float)r->dir.y};
	cube[2] = (t_cube_cmp){&(box->zmin), (float)r->start.z, (float)r->dir.z};
	tb[0] = (double)-INFINITY;
	tb[1] = (double)INFINITY;
	p = 3;
	while (p--)
	{
		if (cube_check(cube[p].box, cube[p].max, cube[p].dir_axis, tb))
			return (0);
		if (tb[1] < 0.0)
			return (0);
	}
	r->lenght = (tb[0] <= 0) ? tb[1] : tb[0];
	if (v)
		rt_cube_setintersect(r, v, tb);
	return (1);
}

int					rt_cube_inter(t_obj *obj, t_ray *r, t_intersect *v)
{
	return (rt_cube_inter_real(r, &obj->hitbox, v));
}

static t_uint		rt_min_index(double *dist, t_uint size)
{
	double		lowest;
	t_uint		id;

	size--;
	id = size;
	lowest = dist[size];
	while (size--)
	{
		if (dist[size] <= lowest)
		{
			lowest = dist[size];
			id = size;
		}
	}
	return (id);
}

t_v4d				rt_cube_normale(t_obj *obj, t_v4d *v)
{
	t_v4d			origin;
	t_uint			lowest_id;
	double			dist[CUBE_SIDES];

	origin = geo_multv4(geo_subv4(*v, obj->trans.w),
			geo_dtov4d((double)((t_cube *)obj->content)->size));
	dist[CUBE_XMAX] = geo_distv4(origin, (t_v4d){1.0, 0.0, 0.0, 0.0});
	dist[CUBE_YMAX] = geo_distv4(origin, (t_v4d){0.0, 1.0, 0.0, 0.0});
	dist[CUBE_ZMAX] = geo_distv4(origin, (t_v4d){0.0, 0.0, 1.0, 0.0});
	dist[CUBE_XMIN] = geo_distv4(origin, (t_v4d){-1.0, 0.0, 0.0, 0.0});
	dist[CUBE_YMIN] = geo_distv4(origin, (t_v4d){0.0, -1.0, 0.0, 0.0});
	dist[CUBE_ZMIN] = geo_distv4(origin, (t_v4d){0.0, 0.0, -1.0, 0.0});
	lowest_id = rt_min_index(dist, CUBE_SIDES);
	if (lowest_id == CUBE_XMAX)
		return ((t_v4d){1.0, 0.0, 0.0, 0.0});
	else if (lowest_id == CUBE_XMIN)
		return ((t_v4d){-1.0, 0.0, 0.0, 0.0});
	else if (lowest_id == CUBE_YMAX)
		return ((t_v4d){0.0, 1.0, 0.0, 0.0});
	else if (lowest_id == CUBE_YMIN)
		return ((t_v4d){0.0, -1.0, 0.0, 0.0});
	else if (lowest_id == CUBE_ZMAX)
		return ((t_v4d){0.0, 0.0, 1.0, 0.0});
	return ((t_v4d){0.0, 0.0, -1.0, 0.0});
}
