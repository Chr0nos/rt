/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 17:29:43 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/28 23:04:51 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

/*
** /!\ DO NOT TOUCH the commented line /!\
** This is an alternative light calcule equation
** latt = geo_lenv4(geo_addv4(r->normal, r->ray->dir)) - 1.0;
*/

void			rt_specular_pow(t_render *r, t_obj *light)
{
	double			latt;
	double			li;
	t_v4d			reflect;
	t_v4d			intelight;

	intelight = geo_normv4(geo_subv4(light->trans.w, r->intersection));
	reflect = (t_v4d){
		intelight.x - 2.0 * geo_dotv4(intelight, r->normal) * r->normal.x,
		intelight.y - 2.0 * geo_dotv4(intelight, r->normal) * r->normal.y,
		intelight.z - 2.0 * geo_dotv4(intelight, r->normal) * r->normal.z,
		0.0
	};
	latt = geo_dotv4(r->ray->dir, reflect);
	li = 0.0;
	if ((latt > 0.0) && (((t_plight *)light->content)->color))
	{
		li = pow(latt, 20) * (((t_plight *)light->content)->intensity);
		r->ray->color = draw_color_lerp(r->ray->color, 0xFFFFFF, (float)
		(li / MID_LIGHT_POWER));
	}
}

void			rt_light_pow(t_render *r, t_obj *light)
{
	double			latt;
	double			li;
	t_cube			*c;

	r->ray->start = r->intersection;
	if (light->type == SUNLIGHT)
	{
		r->light_lenght = (double)INFINITY;
		r->ray->dir = light->trans.y;
	}
	else
	{
		r->light_lenght = geo_distv4(light->trans.w, r->ray->start);
		r->ray->dir = geo_normv4(
			geo_subv4(light->trans.w, r->ray->start));
	}
	r->ray->start = geo_addv4(
		geo_multv4(r->ray->dir, geo_dtov4d(0.0001)), r->ray->start);
	latt = geo_dotv4(r->normal, r->ray->dir);
	if (latt > 0.0)
	{
		li = latt * (((t_plight *)light->content)->intensity);
		c = r->obj_intersect->content;
		r->ray->color = draw_color_lerp(r->ray->color, c->color, (float)
		(li / MID_LIGHT_POWER));
	}
}
