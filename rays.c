/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 01:06:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/23 11:44:44 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "filtre.h"
#include <unistd.h>

static void		rt_debug_ray(t_ray *ray)
{
	static int		limit = 42;

	ft_putstr("start: ");
	draw_putv4d(ray->start, 3);
	ft_putstr(" dir: ");
	draw_putv4d(ray->dir, 5);
	ft_putchar('\n');
	if (!limit--)
		exit(0);
}

static void		rt_rays_pixels(t_rt *rt, t_ray *ray, unsigned int *pixels,
	t_m4 m)
{
	t_v2i			px;
	t_v4d			rad;
	t_camera		*camp;

	(void)rt_debug_ray;
	camp = ((t_obj*)rt->root->content)->content;
	px.x = rt->sys.geometry.x;
	rad = (t_v4d){camp->rayfix.x, 0.0, camp->rayfix.z, camp->rayfix.w};
	while (px.x--)
	{
		px.y = rt->sys.geometry.y;
		rad.y = camp->rayfix.y;
		while (px.y--)
		{
			ray->dir = draw_vector_transform_m4(
				draw_v4d_norm((t_v4d){rad.x, -rad.y, 1.0, 0.0}), &m);
			draw_pxi(pixels, px, (unsigned int)rt->sys.geometry.x,
					filtre(rt_render(rt, ray), rt->filtre));
			rad.y -= rad.w;
		}
		rad.x -= rad.z;
	}
}

void			rt_rays(t_rt *rt)
{
	t_obj		*cam;
	t_camera	*camp;
	t_ray		ray;

	rt->tree = rt_render_tree(rt->root);
	if (rt->tree.memlen == 0)
	{
		ft_putendl_fd("error: failed to malloc tree", 2);
		return ;
	}
	cam = (t_obj*)rt->root->content;
	camp = cam->content;
	rt_update_camera(rt->sys.geometry, cam->content);
	ray.start = cam->trans.w;
	camp->raypos = cam->trans.w;
	ray.limit = 0.0;
	ray.dir = (t_v4d){0.0, 0.0, 1.0, 0.0};
	rt_rays_pixels(rt, &ray, rt->sys.screen->pixels, cam->trans);
	rt->tree.memlen = 0;
	free(rt->tree.bounded);
}
