/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_csg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 17:06:42 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/31 20:29:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static inline int	ray_in_range(t_ray *ray, double min, double max)
{
	return ((ray->lenght < max) && (ray->lenght > min));
}

void				rt_render_csg(t_obj *obj, t_render *r, t_intersect *v)
{
	if (!ray_in_range(r->ray, r->ray->lenght_min, r->ray->lenght_max))
		return ;
	if (!(obj->flags & FLAG_CSG_NEGATIVE))
	{
		r->lowest_lenght = v->len_in;
		r->intersection = v->in;
		r->ray->lenght = v->len_in;
		r->obj_intersect = obj;
		r->ray->intersect = *v;
	}
	else if (v->flags & INTER_OUT)
	{
		if (!ray_in_range(r->ray, v->len_in, v->len_out))
			return ;
		r->ray->lenght_min = v->len_in;
		r->ray->lenght_max = v->len_out;
		r->ray->lenght = v->len_out;
		r->lowest_lenght = v->len_in;
		r->obj_intersect = rt_obj_atpx_real(r->rt, r->ray);
	}
	else if (r->ray->lenght > v->len_in)
	{
		r->ray->lenght_min = v->len_in;
		r->ray->lenght_max = (double)INFINITY;
		r->lowest_lenght = v->len_in;
		r->obj_intersect = rt_obj_atpx_real(r->rt, r->ray);
	}
}

void				rt_render_nocsg(t_obj *obj, t_render *r, t_intersect *v)
{
	r->obj_intersect = obj;
	r->intersection = v->in;
	r->lowest_lenght = r->ray->lenght;
}
