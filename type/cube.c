/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 19:32:17 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 12:15:35 by snicolet         ###   ########.fr       */
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
		*v = draw_v4d_add(r->start,
				draw_v4d_mult(r->dir, (t_v4d){
					r->lenght,
					r->lenght,
					r->lenght,
					0.0
					}));
	}
}

int				rt_cube_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	(void)obj;
	rt_cube_setpos(r, v);
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

	shit = draw_v4d_mult(draw_v4d_sub(*v, obj->trans.w),
			rt_mkvec(1.0 / (double)((t_cube *)obj->content)->size));
	dist[CUBE_XMAX] = draw_v4d_dist(shit, (t_v4d){1.0, 0.0, 0.0, 0.0});
	dist[CUBE_YMAX] = draw_v4d_dist(shit, (t_v4d){0.0, 1.0, 0.0, 0.0});
	dist[CUBE_ZMAX] = draw_v4d_dist(shit, (t_v4d){0.0, 0.0, 1.0, 0.0});
	dist[CUBE_XMIN] = draw_v4d_dist(shit, (t_v4d){-1.0, 0.0, 0.0, 0.0});
	dist[CUBE_YMIN] = draw_v4d_dist(shit, (t_v4d){0.0, -1.0, 0.0, 0.0});
	dist[CUBE_ZMIN] = draw_v4d_dist(shit, (t_v4d){0.0, 0.0, -1.0, 0.0});
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
