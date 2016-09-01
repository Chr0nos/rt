/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_csg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 17:06:42 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/01 18:53:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void				rt_render_csg(t_obj *obj, t_render *r, t_intersect *v)
{
	if (r->ray->lenght >= r->lowest_lenght)
		return ;
	if (r->ray->obj_negative)
	{
		if (r->ray->intersect_negative.len_in < v->len_in)
			return ;
		if (!(r->ray->intersect_negative.flags & INTER_OUT))
			;
		else if (r->ray->intersect_negative.len_out > v->len_out)
			return ;
	}
	if (!(obj->flags & FLAG_CSG_NEGATIVE))
	{
		r->lowest_lenght = v->len_in;
		r->intersection = v->in;
		r->obj_intersect = obj;
		r->ray->lenght = v->len_in;
		r->ray->intersect = *v;
		r->ray->obj_intersect = obj;
		r->ray->obj_negative = NULL;
		//todo: utiliser la normale de l objet negatif pour recuperer ma normale
	}
	// else if (r->ray->obj_negative == obj)
	// 	;
	// bon.. decouverte par serandipite: ca fais des objets en union cette merde
	// else if (r->ray->intersect.len_out < v->len_in)
	// 	;
	else if ((!(v->flags & INTER_OUT)) || (v->len_out < r->lowest_lenght))
	{
		r->obj_intersect = NULL;
		r->ray->obj_intersect = NULL;
		r->ray->obj_negative = obj;
		r->ray->intersect_negative = *v;
		r->ray->lenght_min = v->len_in;
		if (v->flags & INTER_OUT)
		{
			r->ray->lenght_max = v->len_out;
			r->lowest_lenght = v->len_out;
		}
		else
		{
			r->lowest_lenght = v->len_in;
		}
		//rt_render_csg(obj->parent, r, v);
		//rt_render_foreach(obj->parent, PREFIX, r);
	}
}

void				rt_render_nocsg(t_obj *obj, t_render *r, t_intersect *v)
{
	if (r->ray->lenght >= r->lowest_lenght)
		return ;
	r->obj_intersect = obj;
	r->intersection = v->in;
	r->lowest_lenght = r->ray->lenght;
}
