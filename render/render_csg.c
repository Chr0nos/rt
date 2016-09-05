/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_csg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 17:06:42 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/05 18:12:45 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** this function return 1 if the intersect "po" is in inside "v"
** otherwise: 0
*/

static inline int	rt_isvisible(const t_intersect *v, const t_intersect *po)
{
	return ((geo_min(v->len_in, v->len_out) < po->len_in) &&
		(geo_max(v->len_out, v->len_in) > po->len_out) &&
		(geo_min(v->len_out, v->len_in) < po->len_in));
}

/*
** this function unset the current selected objet in the render
** it also set the lowest_lenght to a new value, 0.0 will forbid any other
** search in the render tree, INFINITY will permit any new objet to be selected
*/

static inline void	rt_render_unset(t_render *r, double lowest_lenght)
{
	r->obj_intersect = NULL;
	r->lowest_lenght = lowest_lenght;
}

/*
** this function check for the intersect in the parent by launching a ray at the
** start of the masking object, then we will check if the start is inside or
** outside the negative object
** then we append to the ray lenght the distance from start, because all it's
** distances are from a false starting point we need to compensate
*/

static inline void	rt_render_csg_parent(t_obj *obj, t_ray *nray,
	t_intersect *po, const t_intersect *v)
{
	const double		offset = v->len_in + 0.01;
	const t_v4d			offset_vec = (t_v4d){offset, offset, offset, 1.0};

	(void)offset_vec;
	nray->start = geo_multv4(nray->dir, offset_vec);
	obj->parent->inters(obj->parent, nray, po);
	po->len_in += offset;
	po->len_out += offset;
	nray->lenght += offset;
}

static inline void	rt_render_csg_negative(t_obj *obj, t_render *r,
	t_intersect *v)
{
	t_ray			nray;
	t_intersect		po;

	if ((!obj->parent) || (r->obj_intersect != r->obj_intersect))
		return ;
	if ((!(v->flags & INTER_OUT)) && (obj->parent == r->obj_intersect))
	{
		rt_render_unset(r, 0.0);
		return ;
	}
	nray = *r->ray;
	rt_render_csg_parent(obj, &nray, &po, v);
	if (rt_isvisible(v, &po))
	{
		r->obj_intersect = obj;
		r->ray->lenght = nray.lenght;
		r->lowest_lenght = r->ray->lenght;
	}
	else
		rt_render_unset(r, (double)INFINITY);
}

void				rt_render_csg(t_obj *obj, t_render *r, t_intersect *v)
{
	if (r->ray->lenght >= r->lowest_lenght)
		return ;
	if (!(obj->flags & FLAG_CSG_NEGATIVE))
		rt_render_nocsg(obj, r, v);
	else if ((!(v->flags & INTER_OUT)) || (v->len_out < r->lowest_lenght))
		rt_render_csg_negative(obj, r, v);
}
