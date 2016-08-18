/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_atpx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 13:50:01 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/18 15:47:38 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "objects.h"
#include "render.h"

static t_obj	*obj_atpx_real(t_rt *rt, t_ray *ray)
{
	t_render	r;

	r = (t_render){
		ray, rt,
		NULL,
		HUGE_VAL,
		0.0,
		(t_v4d){0.0, 0.0, 0.0, 0.0},
		ray->dir
	};
	rt_node_foreach(rt->tree.bounded, INFIX, &rt_render_foreach, &r);
	rt_node_foreach(rt->tree.unbounded, INFIX, &rt_render_foreach, &r);
	return (r.obj_intersect);
}

t_obj			*rt_obj_atpx(t_rt *rt, t_v2i px)
{
	t_obj		*obj;
	t_obj		*cam;
	t_camera	*camp;
	t_ray		ray;
	t_v4d		rad;

	cam = rt->root->content;
	camp = cam->content;
	rt_update_camera(rt->sys.geometry, cam->content);
	rad = (t_v4d){camp->rayfix.x, 0.0, camp->rayfix.z, camp->rayfix.w};
	ray.start = cam->trans.w;
	ray.limit = 0.0;
	ray.count = 1;
	((t_camera*)cam->content)->raypos = cam->trans.w;
	rad.x = camp->rayfix.x - (camp->rayfix.z * (rt->sys.geometry.x - px.x));
	rad.y = camp->rayfix.y - (camp->rayfix.w * (rt->sys.geometry.y - px.y));
	ray.dir = geo_m4trans(
		geo_normv4((t_v4d){rad.x, -rad.y, 1.0, 0.0}), &cam->trans);
	geo_putv4d(ray.dir, 6);
	rt->tree = rt_render_tree(rt->root);
	IFRET__(!(obj = obj_atpx_real(rt, &ray)), NULL);
	free(rt->tree.bounded);
	return (obj);
}
