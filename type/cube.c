/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 19:32:17 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/30 16:45:16 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define CUBE_XMIN 0
#define CUBE_XMAX 1
#define CUBE_YMIN 2
#define CUBE_YMAX 3
#define CUBE_ZMIN 4
#define CUBE_ZMAX 5
#define CUBE_SIDES 6

static void		rt_cube_setpos(t_ray *r, t_v4d *v)
{
	if (v)
	{
		*v = geo_addv4(r->start,
				geo_multv4(r->dir, (t_v4d){
					r->lenght,
					r->lenght,
					r->lenght,
					0.0
					}));
	}
}

int				rt_cube_inter(t_obj *obj, t_ray *r, t_intersect *v)
{
	(void)obj;
	rt_cube_setpos(r, &v->in);
	return (1);
}

static t_uint	rt_min_index(double *dist, t_uint size)
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

static t_v4d	rt_mkvec(double a)
{
	return ((t_v4d){a, a, a, 1.0});
}

t_v4d			rt_cube_normale(t_obj *obj, t_v4d *v)
{
	t_v4d			shit;
	t_uint			lowest_id;
	double			dist[CUBE_SIDES];

	shit = geo_multv4(geo_subv4(*v, obj->trans.w),
			rt_mkvec(1.0 / (double)((t_cube *)obj->content)->size));
	dist[CUBE_XMAX] = geo_distv4(shit, (t_v4d){1.0, 0.0, 0.0, 0.0});
	dist[CUBE_YMAX] = geo_distv4(shit, (t_v4d){0.0, 1.0, 0.0, 0.0});
	dist[CUBE_ZMAX] = geo_distv4(shit, (t_v4d){0.0, 0.0, 1.0, 0.0});
	dist[CUBE_XMIN] = geo_distv4(shit, (t_v4d){-1.0, 0.0, 0.0, 0.0});
	dist[CUBE_YMIN] = geo_distv4(shit, (t_v4d){0.0, -1.0, 0.0, 0.0});
	dist[CUBE_ZMIN] = geo_distv4(shit, (t_v4d){0.0, 0.0, -1.0, 0.0});
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
