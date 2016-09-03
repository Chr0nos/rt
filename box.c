/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 21:03:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/31 02:02:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cube.h"
#include "mesh.h"

int				cube_check(float *box, float start, float dir, double *tb)
{
	double	tmin;
	double	tmax;

	tmin = (double)(box[0] - start);
	tmax = (double)(box[1] - start);
	if (dir != 0.0f)
	{
		tmin = tmin / (double)dir;
		tmax = tmax / (double)dir;
		if (tmin > tmax)
			draw_swap(&tmin, &tmax);
	}
	else if ((tmin > 0.0) || (tmax < 0.0))
		return (1);
	else
	{
		tmin = (double)-INFINITY;
		tmax = (double)INFINITY;
	}
	if ((tmin > tb[1]) || (tmax < tb[0]))
		return (1);
	tb[0] = fmax(tb[0], tmin);
	tb[1] = fmin(tb[1], tmax);
	return (0);
}

int				raybox_cube_check(t_ray *r, t_box *box)
{
	double			tb[2];
	const float		rx = (float)r->dir.x;
	const float		ry = (float)r->dir.y;
	const float		rz = (float)r->dir.z;

	tb[0] = (double)-INFINITY;
	tb[1] = (double)INFINITY;
	if (cube_check(&(box->xmin), (float)r->start.x, rx, tb))
		return (0);
	if (tb[1] < 0.0)
		return (0);
	r->lenght = (tb[0] > 0.0) ? tb[0] : tb[1];
	if (cube_check(&(box->ymin), (float)r->start.y, ry, tb))
		return (0);
	if (tb[1] < 0.0)
		return (0);
	r->lenght = (tb[0] > 0.0) ? tb[0] : tb[1];
	if (cube_check(&(box->zmin), (float)r->start.z, rz, tb))
		return (0);
	if (tb[1] < 0.0)
		return (0);
	r->lenght = (tb[0] > 0.0) ? tb[0] : tb[1];
	return (1);
}

static void		rt_box_update_triangle(t_obj *obj)
{
	const t_triangle	*tri = obj->content;
	t_v4d				v[3];
	int					p;

	v[0] = geo_addv4(tri->v3.pos, obj->trans.w);
	v[1] = geo_addv4(tri->v2.pos, obj->trans.w);
	v[2] = geo_addv4(tri->v1.pos, obj->trans.w);
	obj->hitbox = (t_box){(float)v[2].x, (float)v[2].x,
		(float)v[2].y, (float)v[2].y, (float)v[2].z, (float)v[2].z};
	p = 2;
	while (p--)
	{
		if ((float)v[p].x < obj->hitbox.xmin)
			obj->hitbox.xmin = (float)v[p].x;
		if ((float)v[p].y < obj->hitbox.ymin)
			obj->hitbox.ymin = (float)v[p].y;
		if ((float)v[p].z < obj->hitbox.zmin)
			obj->hitbox.zmin = (float)v[p].z;
		if ((float)v[p].x > obj->hitbox.xmax)
			obj->hitbox.xmax = (float)v[p].x;
		if ((float)v[p].y > obj->hitbox.ymax)
			obj->hitbox.ymax = (float)v[p].y;
		if ((float)v[p].z > obj->hitbox.zmax)
			obj->hitbox.zmax = (float)v[p].z;
	}
}

static void		rt_box_update_cone(t_obj *obj, const t_v4f *p)
{
	t_v4f	r;

	r.x = (float)(((t_cone *)(obj->content))->angle.w);
	r.y = ((t_cone *)(obj->content))->size;
	obj->hitbox = (t_box){p->x - r.x * r.y, p->x + r.x * r.y, p->y - r.y,
		p->y, p->z - r.x * r.y, p->z + r.x * r.y};
}

void			rt_box_update(t_obj *obj)
{
	const t_v4f		p = draw_convert_v4d_to_v4f(obj->trans.w);
	t_v4f			r;

	if (obj->type == CUBE)
	{
		r.x = ((t_cube*)(obj->content))->size / 2.0f;
		obj->hitbox = (t_box){p.x - r.x, p.x + r.x, p.y - r.x, p.y + r.x,
			p.z - r.x, p.z + r.x};
	}
	else if (obj->type == SPHERE)
	{
		r.x = ((t_sphere*)(obj->content))->radius;
		obj->hitbox = (t_box){p.x - r.x, p.x + r.x, p.y - r.x, p.y + r.x,
			p.z - r.x, p.z + r.x};
	}
	else if (obj->type == CONE)
		rt_box_update_cone(obj, &p);
	else if (obj->type == TRIANGLE)
		rt_box_update_triangle(obj);
	else
		obj->hitbox = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
}
