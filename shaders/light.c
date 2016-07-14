/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 17:29:43 by qloubier          #+#    #+#             */
/*   Updated: 2016/07/14 21:33:49 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"
#include "shaders.h"

/*
** /!\ DO NOT TOUCH the commented line /!\
** This is an alternative light calcule equation
** latt = geo_lenv4(geo_addv4(r->normal, r->ray->dir)) - 1.0;
*/

void			rt_specular_pow(t_shader *s, t_render *r, t_obj *light)
{
	double			latt;
	double			li;
	t_v4d			reflect;
	t_v4d			intelight;
	unsigned int	color;

	(void)s;
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
		li = (pow(latt, 20) * (((t_plight *)light->content)->intensity) /
		(r->light_lenght / 5.0))
			/ MID_LIGHT_POWER * 255.0;
		color = to_rgb(0, (unsigned int)li, (unsigned int)li, (unsigned int)li);
		s->color_render = blend_lighten(s->color_render, color);
	}
}

void			rt_light_pow(t_shader *s, t_render *r, t_obj *light)
{
	double			latt;
	double			li;
	unsigned int	color;
	t_v4d			light_vector;

	light_vector = geo_normv4(geo_subv4(light->trans.w, r->intersection));
	r->light_lenght = geo_distv4(light->trans.w, r->intersection);
	// t_ray			temp_ray;
	//
	// temp_ray = *r->ray;
	// temp_ray.start = r->intersection;
	// if (light->type == SUNLIGHT)
	// {
	// 	r->light_lenght = (double)INFINITY;
	//  	light_vector = light->trans.y;
	// }
	// else
	// {
	// 	r->light_lenght = geo_distv4(light->trans.w, r->intersection);
	// 	temp_ray.dir = geo_normv4(
	// 		geo_subv4(light->trans.w, temp_ray.start));
	// }
	// temp_ray.start = geo_addv4(
	// 	geo_multv4(temp_ray.dir, geo_dtov4d(0.0001)), temp_ray.start);
	latt = geo_dotv4(r->normal, light_vector);
	if (latt > 0.0)
	{
		li = ((latt * (((t_plight *)light->content)->intensity)) * 2.0) /
		(light->type & SUNLIGHT ? 1.0 : (r->light_lenght / 10.0));
		color = to_rgb(0, (unsigned int)li, (unsigned int)li, (unsigned int)li);
		color = (color > 0xB0B0B0 ? 0xB0B0B0 : color);
		s->color_render = blend_lighten(s->color_render, color);
	}
}
