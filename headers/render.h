/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 00:08:43 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/29 14:06:50 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "rt.h"

# define MID_LIGHT_POWER	100.0
# define MAX_LIGHT_POWER	800.0

typedef struct	s_render
{
	t_ray		*ray;
	t_rt		*rt;
	t_obj		*obj_intersect;
	double		lowest_lenght;
	double		light_lenght;
	t_v4d		intersection;
	t_v4d		normal;
	double		light_power;
	double		specular_power;
}				t_render;

t_uint			rt_render(t_rt *rt, t_ray *ray);
void			rt_light_pow(t_render *r, t_obj *light);
void			rt_specular_pow(t_render *r, t_obj *light);
double			rt_checker(t_render *r, t_obj *light);
unsigned int	rt_render_opacity(t_rt *rt, const t_ray *ray,
	const t_render *r);
int				rt_render_light(t_obj *obj, int mode, void *userdata);
int				rt_render_shadow(t_obj *obj, int mode, void *userdata);
int				rt_render_foreach(t_obj *obj, int mode, void *userdata);
t_uint			apply_texture(t_obj *cur, t_render *r);

#endif
