/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 00:08:43 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:43:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "rt.h"

# define MID_LIGHT_POWER	100.0
# define MAX_LIGHT_POWER	800.0

typedef	struct s_rt	t_rt;

typedef struct		s_render
{
	t_ray			*ray;
	t_rt			*rt;
	t_obj			*obj_intersect;
	double			lowest_lenght;
	double			light_lenght;
	t_v4d			intersection;
	t_v4d			normal;
	unsigned int	*colors_renders;
}					t_render;

void				rt_init_rt_rendermode(t_rt *rt, void (*cbf)(t_rt *));

t_uint				rt_render_ray(t_rt *rt, t_ray *ray);
unsigned int		rt_render_opacity(t_rt *rt, const t_ray *ray,
	const t_render *r);
void				rt_render_csg(t_obj *obj, t_render *r, t_intersect *v);
void				rt_render_nocsg(t_obj *obj, t_render *r, t_intersect *v);
int					rt_render_light(t_obj *obj, int mode, void *userdata);
int					rt_render_shadow(t_obj *obj, int mode, void *userdata);
int					rt_render_foreach(t_obj *obj, int mode, void *userdata);

#endif
