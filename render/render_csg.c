/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_csg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 17:06:42 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/31 17:45:00 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void			rt_render_csg(t_obj *obj, t_render *r, t_intersect *v)
{
	const char		on = obj->flags & FLAG_CSG_NEGATIVE;
	const char		rn = r->ray->flags & FLAG_CSG_NEGATIVE;

	r->lowest_lenght = v->len_in;
	r->obj_intersect = obj;
	//p + p = p
	if ((!on) && (!rn))
	{
		r->intersection = v->in;
	}
	//n + p = n
	if ((on) && (!rn))
	{
		r->ray->flags |= FLAG_CSG_NEGATIVE;
		//r->lowest_lenght = v->len_in;
		if (v->flags & INTER_OUT)
		{
			//r->obj_intersect = obj->parent;
		}
	}
	//n + n = p
	if ((on) && (rn))
	{
		r->ray->flags &= ~FLAG_CSG_NEGATIVE;
		r->ray->lenght = v->len_in;
		r->intersection = v->in;
	}
	//p + n = n
	if ((on) && (!rn))
	{
		r->ray->flags |= FLAG_CSG_NEGATIVE;
	}
}

void			rt_render_nocsg(t_obj *obj, t_render *r, t_intersect *v)
{
	r->obj_intersect = obj;
	r->intersection = v->in;
	r->lowest_lenght = r->ray->lenght;
}
