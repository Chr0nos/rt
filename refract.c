/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 17:01:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/28 18:01:14 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

/*
** rfi : refractive_index (double)
*/

static t_v4d	rt_ray_refract(const t_render *r, const t_ray *ray)
{
	const double	*rfi = &r->obj_intersect->refractive_index;
	const double	cosa = geo_dotv4(r->normal, geo_invv4(ray->dir));
	const double	cosb = sqrt(1 - pow(1.0 / *rfi, 2.0) *
		(1 - pow(cosa, 2.0)));
	const double	coef = (cosa > 0.0 ? -1.0 : 1.0);

	return ((t_v4d) {
		(1.0 / *rfi) * ray->dir.x +	((1.0 / *rfi) * cosa + cosb * coef)
		* r->normal.x,
		(1.0 / *rfi) * ray->dir.y + ((1.0 / *rfi) * cosa + cosb *
		coef) * r->normal.y,
		(1.0 / *rfi) * ray->dir.z + ((1.0 / *rfi) * cosa +
		cosb * coef) * r->normal.z,
		0.0
	});
}

unsigned int	rt_render_opacity(t_rt *rt, const t_ray *ray, const t_render *r)
{
	unsigned char			alpha;
	t_ray					nray;

	if (!r->obj_intersect)
		return (ray->color);
	alpha = (((t_cube*)r->obj_intersect->content)->color & 0xff000000) >> 24;
	if (!alpha)
		return (ray->color);
	nray = *ray;
	nray.start = geo_addv4(r->intersection, geo_multv4(ray->dir,
		geo_dtov4d(0.01)));

	nray.dir = rt_ray_refract(r, ray);
	return (draw_color_lerp(ray->color, rt_render(rt, &nray),
		(float)alpha / 255.0f));
}
