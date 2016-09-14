/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 17:29:43 by qloubier          #+#    #+#             */
/*   Updated: 2016/09/14 16:24:34 by alhote           ###   ########.fr       */
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

static t_v4d		rt_specular_pow_intelight(t_obj *light, t_render *r)
{
	return ((light->type & SUNLIGHT ?
		geo_normv4(light->trans.w) :
		geo_normv4(geo_subv4(light->trans.w, r->intersection))));
}

void				rt_specular_pow(t_shader *s, t_render *r, t_obj *light,
		unsigned int *color_render)
{
	double			latt;
	double			li;
	t_v4d			reflect;
	const t_v4d		intelight = rt_specular_pow_intelight(light, r);
	const double	dot = 2.0 * geo_dotv4(intelight, r->normal);

	(void)s;
	reflect = (t_v4d){
		intelight.x - dot * r->normal.x,
		intelight.y - dot * r->normal.y,
		intelight.z - dot * r->normal.z,
		0.0
	};
	latt = geo_dotv4(r->ray->dir, reflect);
	if ((latt > 0.0) && (((t_plight *)light->content)->color))
	{
		li = (pow(latt, 20) * (((t_plight *)light->content)->intensity) /
		(light->type & SUNLIGHT ? 1.0 : (r->light_lenght / 5.0)))
			/ MID_LIGHT_POWER * 255.0;
		*color_render = blend_lighten(*color_render,
			blend_multiply(((t_cube*)(light->content))->color,
			to_rgb(0, (unsigned int)li, (unsigned int)li, (unsigned int)li)));
	}
}

/*
** ambiant light and diffuse
*/

static t_obj		*relaunch_ray(t_v4d pos, t_v4d dir, t_render *r)
{
	t_ray			ray;
	t_render		sw;

	ray.dir = dir;
	ray.start = pos;
	ray.count = 2;
	sw = (t_render){&ray, r->rt, NULL, HUGE_VAL, 0.0,
			(t_v4d){0.0, 0.0, 0.0, 0.0}, dir, 0};
	rt_node_foreach(sw.rt->tree.bounded, INFIX, &rt_render_foreach, &sw);
	rt_node_foreach(sw.rt->tree.unbounded, INFIX, &rt_render_foreach, &sw);
	return (sw.obj_intersect);
}

void				rt_light_pow(t_shader *s, t_render *r, t_obj *light,
		unsigned int *color_render)
{
	double			latt;
	double			li;
	unsigned int	color;
	t_v4d			light_vector;

	(void)s;
	light_vector = (light->type & SUNLIGHT ? geo_normv4(light->trans.w) :
		geo_normv4(geo_subv4(light->trans.w, r->intersection)));
	r->light_lenght = (light->type & SUNLIGHT ? (double)INFINITY :
		geo_distv4(light->trans.w, r->intersection));
	latt = geo_dotv4(r->normal, light_vector);
	if (latt > 0.0 || (A(shader_color_texture_intersection(r)) &&
		!relaunch_ray(geo_addv4(r->intersection,
			geo_multv4(light_vector, geo_dtov4d(0.00001))), light_vector, r)))
	{
		latt = (latt < 0.0 ? -latt : latt);
		li = ((latt * (((t_plight *)light->content)->intensity)) * 2.0) /
			(light->type & SUNLIGHT ? 1.0 : (r->light_lenght * 0.1));
		color = blend_multiply(((t_cube*)(light->content))->color,
		to_rgb(0, (unsigned int)li, (unsigned int)li, (unsigned int)li));
		color = blend_lighten(color, r->rt->settings.ambiant_light);
	}
	else
		color = r->rt->settings.ambiant_light;
	*color_render = blend_lighten(*color_render, color);
}
