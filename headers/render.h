/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 00:08:43 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/22 17:07:22 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "rt.h"

# define MID_LIGHT_POWER 100.0
# define MAX_LIGHT_POWER 800.0

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

double			rt_light_pow(t_render *r, t_obj *light);
double			rt_specular_pow(t_render *r, t_obj *light);

#endif
