/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 18:03:40 by alhote            #+#    #+#             */
/*   Updated: 2016/09/11 14:38:48 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mesh.h"
#define EPSILON 0.000001

static inline int	rt_triangle_inter2(t_ray *r, t_intersect *v, const double t)
{
	v->in = geo_addv4(r->start, geo_multv4(r->dir, geo_dtov4d(t)));
	v->len_in = t;
	v->flags = INTER_IN;
	r->lenght = t;
	return (1);
}

/*
** triangle->normal_fix = 0;
**
** if (geo_dotv4(r->dir, rt_triangle_normale(obj, &impact->in)) > 0.0)
**	triangle->normal_fix = 0;
*/

int					rt_triangle_inter(t_obj *obj, t_ray *r, t_intersect *impact)
{
	t_v4d			e[2];
	t_v4d			pqt[3];
	double			det;
	double			uvt[3];
	t_triangle		*triangle;

	triangle = obj->content;
	e[0] = geo_subv4(triangle->v2.pos, triangle->v1.pos);
	e[1] = geo_subv4(triangle->v3.pos, triangle->v1.pos);
	pqt[0] = geo_crossv4(r->dir, e[1]);
	if ((det = geo_dotv4(e[0], pqt[0])) > -EPSILON && det < EPSILON)
		return (0);
	det = 1.0 / det;
	pqt[2] = geo_subv4(r->start, geo_addv4(obj->trans.w, triangle->v1.pos));
	uvt[0] = geo_dotv4(pqt[2], pqt[0]) * det;
	pqt[1] = geo_crossv4(pqt[2], e[0]);
	uvt[1] = geo_dotv4(r->dir, pqt[1]) * det;
	uvt[2] = geo_dotv4(e[1], pqt[1]) * det;
	if ((uvt[0] < 0.0) || (uvt[0] > 1.0) || (uvt[1] < 0.0) ||
		(uvt[0] + uvt[1] > 1.0) || (uvt[2] < EPSILON))
		return (0);
	return (rt_triangle_inter2(r, impact, uvt[2]));
}

t_v4d				rt_triangle_normale(t_obj *obj, t_v4d *v)
{
	t_v4d		e1;
	t_v4d		e2;
	t_triangle	*triangle;

	(void)v;
	triangle = obj->content;
	e1 = geo_subv4(triangle->v2.pos, triangle->v1.pos);
	e2 = geo_subv4(triangle->v3.pos, triangle->v1.pos);
	return (geo_normv4(geo_crossv4(e1, e2)));
}
