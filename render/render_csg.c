/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_csg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 17:06:42 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 07:47:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static inline int	rt_isvisible(const t_intersect *v, const t_intersect *po)
{
	return ((geo_min(v->len_in, v->len_out) < po->len_in) &&
		(geo_max(v->len_out, v->len_in) > po->len_out) &&
		(geo_min(v->len_out, v->len_in) < po->len_in));
}

static inline void	rt_render_csg_negative(t_obj *obj, t_render *r,
	t_intersect *v)
{
	t_ray			nray;
	t_intersect		po;

	if (!obj->parent)
		return ;
	//si le batard d objet negatif il a pas de putain de point de sortie on baise le batard de parent
	if ((!(v->flags & INTER_OUT)) && (obj->parent == r->obj_intersect))
	{
		r->ray->obj_intersect = NULL;
		r->obj_intersect = NULL;
		r->lowest_lenght = 0.0;
		return ;
	}
	//on copie le batard de rayon
	nray = *r->ray;
	//futur moi, n active pas ca, tu va decaller toutes les valeurs de po sinon et tu va pleurer ta mere
	//nray.start = geo_multv4(nray.dir, geo_dtov4d(v->len_out));
	obj->parent->inters(obj->parent, &nray, &po);
	//si le parent se trouve dans le batard d objet negatif on fix le rayon
	if (rt_isvisible(v, &po))
	//if ((po.len_in > v->len_in) && (po.len_in < v->len_out))
	{
		r->obj_intersect = obj;
		r->ray->obj_intersect = obj;
		r->ray->lenght = geo_min(po.len_in, po.len_out);
		r->lowest_lenght = r->ray->lenght;
	}
	//sinon delete le batard d'objet parent car.... il fais chier et devrais pas etre la
	else
	{
		r->ray->obj_intersect = NULL;
		r->obj_intersect = NULL;
		r->lowest_lenght = (double)INFINITY;
	}
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

void				rt_render_nocsg(t_obj *obj, t_render *r, t_intersect *v)
{
	if (r->ray->lenght >= r->lowest_lenght)
		return ;
	r->obj_intersect = obj;
	r->intersection = v->in;
	r->lowest_lenght = r->ray->lenght;
}
