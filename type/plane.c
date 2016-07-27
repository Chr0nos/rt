/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 19:00:18 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/27 13:02:27 by hantlowt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
static int	rt_heightmap(t_obj *obj, t_ray *r, t_v4d *v)
{
	int		x;
	int		y;
	double	t;
	double	best_dist;
	int		check;
	const unsigned int	*px =
	((t_plan*)obj->content)->heightmap->surface->pixels;
	x = 0;
	y = 0;
	t = 0.0;
	check = 0;
	best_dist = (double)INFINITY;
	while (y < ((t_plan*)obj->content)->heightmap->surface->h)
	{
		while (x < ((t_plan*)obj->content)->heightmap->surface->w)
		{
			t = (-(int)r->start.x-(int)r->start.z+(double)x + (double)y)/(r->dir.x+r->dir.z);
			// t = geo_dotv4(obj->trans.y, r->dir);
			// t = -geo_dotv4(obj->trans.y, geo_subv4(r->start, geo_addv4(obj->trans.w, (t_v4d){
			// 	(double)x,
			// 	(double)y,
			// 	(double)px[((t_plan*)obj->content)->heightmap->surface->w * y + x],
			// 	1.0}))) / t;
			if (t > 0.0 && t < best_dist && r->start.y + r->dir.y * t >= 0.0 &&
				r->start.x + r->dir.x * t >= 0.0 &&
				r->start.x + r->dir.x * t <= (double)((t_plan*)obj->content)->heightmap->surface->w &&
				r->start.y + r->dir.y * t <= obj->trans.w.y + (double)(px[((t_plan*)obj->content)->heightmap->surface->w * y + x] & 0xFF) / 100.0)
			{
				check = 1;
				best_dist = t;
			}
			++x;
		}
		y++;
	}
	*v = (t_v4d){
		r->start.x + r->dir.x * best_dist,
		r->start.y + r->dir.y * best_dist,
		r->start.z + r->dir.z * best_dist,
		0.0
	};
	r->lenght = t;
	return (check ? 1 : 0);
}

int			rt_plane_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	const t_v4d		plane = obj->trans.y;
	double			t;

	if (((t_plan*)obj->content)->heightmap)
		return(rt_heightmap(obj, r, v));
	t = geo_dotv4(plane, r->dir);
	if (t == 0.0)
		return (0);
	t = -geo_dotv4(plane, geo_subv4(r->start, obj->trans.w)) / t;
	if (t < 0.0)
		return (0);
	if (v)
		*v = (t_v4d){
			r->start.x + r->dir.x * t,
			r->start.y + r->dir.y * t,
			r->start.z + r->dir.z * t,
			0.0
		};
	r->lenght = t;
	return (1);
}

t_v4d	rt_plane_normale(t_obj *obj, t_v4d *v)
{
	(void)v;
	return (obj->trans.y);
}
