/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 17:29:43 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/21 18:49:14 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

/*
** /!\ DO NOT TOUCH the commented line /!\
** This is an alternative light calcule equation
*/

double			rt_light_pow(t_render *r, t_obj *light)
{
	double			latt;
	double			li;

	r->ray->start = r->intersection;
	if (light->type == SUNLIGHT)
	{
		r->light_lenght = (double)INFINITY;
		r->ray->dir = light->trans.y;
		// latt = draw_v4d_len(draw_v4d_add(r->normal, r->ray->dir)) - 1.0;
	}
	else
	{
		r->light_lenght = draw_v4d_dist(light->trans.w, r->ray->start);
		r->ray->dir = draw_v4d_norm(
			draw_v4d_sub(light->trans.w, r->ray->start));
	}
	r->ray->start = draw_v4d_add(
		draw_v4d_mult(r->ray->dir, draw_dtov4d(0.0001)), r->ray->start);
	latt = draw_v4d_dot(r->normal, r->ray->dir);
	li = 0.0;
	if (latt > 0.0)
		li = latt * (((t_plight *)light->content)->intensity);
	return (li);
}
