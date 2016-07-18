/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 00:08:43 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 17:25:29 by alhote           ###   ########.fr       */
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
}				t_render;

t_uint			rt_render_ray(t_rt *rt, t_ray *ray);
unsigned int	rt_render_opacity(t_rt *rt, const t_ray *ray,
	const t_render *r);
int				rt_render_light(t_obj *obj, int mode, void *userdata);
int				rt_render_shadow(t_obj *obj, int mode, void *userdata);
int				rt_render_foreach(t_obj *obj, int mode, void *userdata);

#endif
