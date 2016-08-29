/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 18:03:40 by alhote            #+#    #+#             */
/*   Updated: 2016/08/29 16:07:42 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mesh.h"
#define EPSILON 0.000001

static int		rt_triangle_inter2(t_ray *r, t_v4d *i, double t)
{
	*i = (t_v4d){r->start.x + r->dir.x * t, r->start.y + r->dir.y * t, \
	r->start.z + r->dir.z * t, 0.0};
	r->lenght = t;
	return (1);
}

int				rt_triangle_inter(t_obj *obj, t_ray *r, t_v4d *i)
{
	t_v4d			e[2];
	t_v4d			pqt[3];
	double			det;
	double			uvt[3];
	t_triangle		*triangle;

	triangle = obj->content;
	triangle->normal_fix = 0;
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
	if (uvt[0] < 0.0 || uvt[0] > 1.0 || uvt[1] < 0.0 || uvt[0] + uvt[1] > 1.0
			|| uvt[2] < EPSILON)
		return (0);
	if (geo_dotv4(r->dir, rt_triangle_normale(obj, i)) > 0.0)
		triangle->normal_fix = 1;
	return (rt_triangle_inter2(r, i, uvt[2]));
}

t_v4d			rt_triangle_normale(t_obj *obj, t_v4d *v)
{
	t_v4d		e1;
	t_v4d		e2;
	t_triangle	*triangle;

	(void)v;
	triangle = obj->content;
	e1 = geo_subv4(triangle->v2.pos, triangle->v1.pos);
	e2 = geo_subv4(triangle->v3.pos, triangle->v1.pos);
	return ((triangle->normal_fix ? geo_invv4(geo_normv4(geo_crossv4(e1, e2)))
	: geo_normv4(geo_crossv4(e1, e2))));
}
