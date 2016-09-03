/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_atpx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 13:50:01 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/02 03:29:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "objects.h"
#include "render.h"
#include "shaders.h"
#include "sda.h"

/*
** for textured objects we need to compute the position of the texture
** for this we directly use the shader system withous using the light system
** in case of the texture shader is disabled on the objects
** the raw color of the object will be unsed to retrive the alpha
** if the alpha is == to 0xff then the item will NOT be selected and considered
** as invisible
*/

static void		obj_atpx_texture(t_render *r)
{
	t_shader		*s;
	unsigned int	color;

	s = sda_setup_getshader_addr(r->obj_intersect->shader->shader,
		(void*)(unsigned long)&shader_texture);
	if ((!s) || (!s->enabled))
	{
		r->ray->color = ((t_cube*)r->obj_intersect->content)->color;
		return ;
	}
	s->exec(s, r, NULL, &color);
	r->ray->color = s->blend(color, s->color_base);
}

t_obj			*rt_obj_atpx_real(t_rt *rt, t_ray *ray)
{
	t_render	r;

	r = (t_render){
		ray, rt, NULL, HUGE_VAL,
		0.0, (t_v4d){0.0, 0.0, 0.0, 0.0},
		ray->dir,
		NULL
	};
	ray->color = 0xff000000;
	rt_node_foreach(rt->tree.bounded, INFIX, &rt_render_foreach, &r);
	rt_node_foreach(rt->tree.unbounded, INFIX, &rt_render_foreach, &r);
	if (!r.obj_intersect)
		return (NULL);
	if (!(r.obj_intersect->cfgbits & SDB_TEXTURE))
		ray->color = ((t_cube*)r.obj_intersect->content)->color;
	else
		obj_atpx_texture(&r);
	if (A(ray->color) == 0xff)
	{
		ray->start = geo_addv4(r.intersection, geo_multv4(ray->dir,
			geo_dtov4d(0.01)));
		return (rt_obj_atpx_real(rt, ray));
	}
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
	obj = rt_obj_atpx_real(rt, &ray);
	free(rt->tree.bounded);
	return ((obj) ? rt_obj_byid(rt->root, obj->id) : NULL);
}
