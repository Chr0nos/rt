/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 18:03:40 by alhote            #+#    #+#             */
/*   Updated: 2016/08/01 21:46:33 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mesh.h"
#define EPSILON 0.000001

int				rt_triangle_inter(t_obj *obj, t_ray *r, t_v4d *i)
{
	t_v4d		e1;
	t_v4d		e2;
	t_v4d		P;
	t_v4d		Q;
	t_v4d		T;
	double		det;
	double		inv_det;
	double		u;
	double		v;
	double		t;
	t_triangle	*triangle;

	triangle = obj->content;
	e1 = geo_subv4(triangle->v2.pos, triangle->v1.pos);
	e2 = geo_subv4(triangle->v3.pos, triangle->v1.pos);
	P = geo_multv4(r->dir, e2);
	det = geo_dotv4(e1, P);
	if (det > -EPSILON && det < EPSILON)
		return (0);
	inv_det = 1.0 / det;
	T = geo_subv4(r->start, triangle->v1.pos);
	u = geo_dotv4(T, P) * inv_det;
	if (u < 0.0 || u > 1.0)
		return (0);
	Q = geo_multv4(T, e1);
	v = geo_dotv4(r->dir, Q) * inv_det;
	if (v < 0.0 || u + v  > 1.0)
		return (0);
	t = geo_dotv4(e2, Q) * inv_det;
	if (t < EPSILON)
		return (0);
	*i = (t_v4d){r->start.x + r->dir.x * t, r->start.y + r->dir.y * t, \
	r->start.z + r->dir.z * t, 0.0};
	return (1);
}

t_v4d			rt_triangle_normal(t_obj *obj, t_v4d *v)
{
	t_v4d		e1;
	t_v4d		e2;
	t_triangle	*triangle;

	(void)v;
	triangle = obj->content;
	e1 = geo_subv4(triangle->v2.pos, triangle->v1.pos);
	e2 = geo_subv4(triangle->v3.pos, triangle->v1.pos);
	return (geo_normv4(geo_multv4(e1, e2)));
}
